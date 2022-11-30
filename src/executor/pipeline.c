/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:33:32 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/30 13:18:45 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

void	close_pipeline(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
		close_pipeline(root->left);
	if (root->right)
		close_pipeline(root->right);
	if (root->type == TREE_TYPE_PIPE && root->content)
	{
		close_safe(((int *)root->content)[0]);
		close_safe(((int *)root->content)[1]);
		free(root->content);
		root->content = NULL;
	}
}

void	execution_sync(t_exec *exec)
{
	t_cmd	*cmd;
	t_bool	coredump;

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
	close_pipeline(exec->commands);
	if (exec->commands)
		destroy_tree(exec->commands, destroy_execution_tree);
	if (exec->queue)
		destroy_queue(exec->queue, NULL);
	free(exec);
}
