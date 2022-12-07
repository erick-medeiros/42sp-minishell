/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/07 12:17:00 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus.h"
#include "executor_bonus.h"
#include "minishell_bonus.h"
#include "parser_bonus.h"

void	executor(t_ms *ms)
{
	t_exec	*exec;
	t_queue	queue;
	t_tree	*root;

	root = build_tree_postfix(ms);
	exec = malloc(sizeof(t_exec));
	exec->commands = root;
	queue.front = NULL;
	queue.rear = NULL;
	exec->queue = &queue;
	exec->env = &ms->env_list;
	free_minishell(ms);
	tree_executor(exec, exec->commands, STDIN, STDOUT);
	close_pipeline(exec->commands);
	execution_sync(exec);
	destroy_exec(exec);
}

void	tree_executor(t_exec *exec, t_tree *node, int in, int out)
{
	t_cmd	*cmd;

	if (!node)
		return ;
	if (node->type == TREE_TYPE_CMD)
	{
		cmd = node->content;
		cmd->piping[0] = in;
		cmd->piping[1] = out;
		execute_command(exec, cmd);
		enqueue(exec->queue, cmd);
	}
	else if (node->type == TREE_TYPE_PIPE)
		tree_pipe_executor(exec, node, in, out);
	else if (node->type == TREE_TYPE_AND || node->type == TREE_TYPE_OR)
		tree_list_executor(exec, node, in, out);
	else if (node->type == TREE_TYPE_GROUP)
		tree_group_executor(exec, node, in, out);
}

void	tree_pipe_executor(t_exec *exec, t_tree *node, int in, int out)
{
	int	*pfd;

	pfd = malloc(sizeof(int) * 2);
	if (pipe(pfd) == -1)
		error_message1(1, "pipe failed");
	node->content = pfd;
	if (node->left && node->left->type == TREE_TYPE_CMD)
		((t_cmd *)node->left->content)->ispipeline = TRUE;
	tree_executor(exec, node->left, in, pfd[1]);
	if (node->right && node->right->type == TREE_TYPE_CMD)
		((t_cmd *)node->right->content)->ispipeline = TRUE;
	tree_executor(exec, node->right, pfd[0], out);
}

void	tree_list_executor(t_exec *exec, t_tree *node, int in, int out)
{
	if (node->type == TREE_TYPE_AND)
	{
		tree_executor(exec, node->left, in, out);
		close_safe_pipeline(exec->commands, in, out);
		execution_sync(exec);
		if (exec->env->last_status == 0)
			tree_executor(exec, node->right, in, out);
	}
	else if (node->type == TREE_TYPE_OR)
	{
		tree_executor(exec, node->left, in, out);
		close_safe_pipeline(exec->commands, in, out);
		execution_sync(exec);
		if (exec->env->last_status != 0)
			tree_executor(exec, node->right, in, out);
	}
}

void	tree_group_executor(t_exec *exec, t_tree *node, int in, int out)
{
	t_cmd	*cmd;

	if (!node || !node->left)
		return ;
	cmd = node->content;
	redirect_command_list(exec, node->left, cmd->redirect);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		tree_executor(exec, node->left, in, out);
		close_pipeline(exec->commands);
		execution_sync(exec);
		builtin_exit(exec, exec->env->last_status);
	}
	enqueue(exec->queue, cmd);
}
