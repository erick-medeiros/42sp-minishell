/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/26 14:13:41 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "minishell.h"

void	executor(t_tree *root, t_vlst *env)
{
	t_exec	*exec;
	t_queue	queue;

	exec = malloc(sizeof(t_exec));
	exec->commands = root;
	queue.front = NULL;
	queue.rear = NULL;
	exec->queue = &queue;
	exec->env = env;
	tree_executor(exec, exec->commands, STDIN, STDOUT);
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
		cmd->input = in;
		cmd->output = out;
		execute_command(exec, cmd, exec->env);
		enqueue(exec->queue, cmd);
	}
	else if (node->type == TREE_TYPE_PIPE)
		tree_pipe_executor(exec, node, in, out);
	else if (node->type == TREE_TYPE_AND || node->type == TREE_TYPE_OR)
		tree_list_executor(exec, node, in, out);
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
	tree_right_executor(exec, node->right, pfd[0], out);
}

void	tree_list_executor(t_exec *exec, t_tree *node, int in, int out)
{
	if (node->type == TREE_TYPE_AND)
	{
		tree_executor(exec, node->left, in, out);
		execution_sync(exec);
		if (exec->env->last_status == 0)
			tree_right_executor(exec, node->right, in, out);
	}
	else if (node->type == TREE_TYPE_OR)
	{
		tree_executor(exec, node->left, in, out);
		execution_sync(exec);
		if (exec->env->last_status != 0)
			tree_right_executor(exec, node->right, in, out);
	}
}

void	tree_right_executor(t_exec *exec, t_tree *node, int in, int out)
{
	t_cmd	*cmd;
	pid_t	pid;

	if (!node)
		return ;
	if (node->type == TREE_TYPE_CMD)
	{
		tree_executor(exec, node, in, out);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		tree_executor(exec, node, in, out);
		execution_sync(exec);
		builtin_exit(exec, 0);
	}
	cmd = new_command();
	cmd->die_in_queue = TRUE;
	cmd->pid = pid;
	enqueue(exec->queue, cmd);
}
