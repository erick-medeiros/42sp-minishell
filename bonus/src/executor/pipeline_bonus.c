/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:33:32 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/07 19:59:28 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_bonus.h"
#include "minishell_bonus.h"

void	close_tree_redirects(t_tree *root, int in, int out)
{
	int	*pfd;

	if (root && root->left)
		close_tree_redirects(root->left, in, out);
	if (root && root->right)
		close_tree_redirects(root->right, in, out);
	if (root && root->type == TREE_TYPE_PIPE && root->content)
	{
		pfd = root->content;
		if (pfd[0] != in && pfd[0] != out)
			close_safe(pfd[0]);
		if (pfd[1] != in && pfd[1] != out)
			close_safe(pfd[1]);
		free(root->content);
		root->content = NULL;
	}
	else if (root && root->type == TREE_TYPE_GROUP && root->content)
	{
		pfd = ((t_cmd *)root->content)->redir;
		if (pfd[0] != in && pfd[0] != out)
			pfd[0] = close_safe(pfd[0]);
		if (pfd[1] != in && pfd[1] != out)
			pfd[1] = close_safe(pfd[1]);
	}
}

void	execution_sync(t_exec *exec, int in, int out)
{
	t_cmd	*cmd;
	t_bool	coredump;

	close_tree_redirects(exec->commands, in, out);
	coredump = FALSE;
	cmd = dequeue(exec->queue);
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &cmd->status, 0);
			if (WIFEXITED(cmd->status))
				cmd->status = WEXITSTATUS(cmd->status);
			else if (WIFSIGNALED(cmd->status))
			{
				coredump = WCOREDUMP(cmd->status);
				cmd->status = 128 + WTERMSIG(cmd->status);
			}
		}
		exec->env->last_status = cmd->status;
		cmd = dequeue(exec->queue);
	}
	print_signal_error(exec->env->last_status, coredump);
}

void	destroy_exec(t_exec *exec)
{
	close_tree_redirects(exec->commands, STDIN, STDOUT);
	if (exec->commands)
		destroy_tree(exec->commands, destroy_execution_tree);
	if (exec->queue)
		destroy_queue(exec->queue, NULL);
	free(exec);
}
