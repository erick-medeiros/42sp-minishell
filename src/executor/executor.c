/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 19:29:48 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "minishell.h"
#include "parser.h"

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
	else
		tree_pipe_executor(exec, node, in, out);
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
