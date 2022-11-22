/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/22 15:22:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

void	executor(t_minishell *ms)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->commands = NULL;
	exec->pipeline = NULL;
	etree_executor(exec, &ms->env_list, exec->commands);
	destroy_exec(exec);
}

void	etree_executor(t_exec *exec, t_vlst *env, t_etree *node)
{
	int	pipefd[2];

	if (!node)
		return ;
	if (node->next && node->next->operator == OP_PIPE)
	{
		pipe(pipefd);
		node->output = pipefd[WRITE_PIPE];
		node->next->input = pipefd[READ_PIPE];
		node->ispipeline = TRUE;
		node->next->ispipeline = TRUE;
	}
	if (node->group)
		group_executor(exec, env, node);
	else
		execute_command(exec, node, env);
	close_safe(node->input);
	close_safe(node->output);
	enqueue(exec->pipeline, node);
	if (!node->next || node->next->operator != OP_PIPE)
		pipeline_sync(exec->pipeline);
	if (node->next && ((node->next->operator == OP_PIPE)
			|| (node->next->operator == OP_AND && node->status == 0)
			|| (node->next->operator == OP_OR && node->status != 0)))
		etree_executor(exec, env, node->next);
}

void	group_executor(t_exec *exec, t_vlst *env, t_etree *node)
{
	t_etree	*tmp;

	node->pid = fork();
	if (node->pid == 0)
	{
		node->group->input = node->input;
		tmp = node->group;
		while (tmp)
		{
			if (!tmp->next)
				tmp->output = node->output;
			tmp = tmp->next;
		}
		etree_executor(exec, env, node->group);
		destroy_exec(exec);
		exit(0);
	}
}

void	pipeline_sync(t_queue *queue)
{
	t_etree	*node;
	t_bool	coredump;
	int		status;

	coredump = FALSE;
	node = dequeue(queue);
	while (node)
	{
		coredump = FALSE;
		if (node->pid > 0)
		{
			waitpid(node->pid, &node->status, 0);
			if (WIFEXITED(node->status))
				node->status = WEXITSTATUS(node->status);
			else if (WIFSIGNALED(node->status))
			{
				coredump = WCOREDUMP(node->status);
				node->status = 128 + WTERMSIG(node->status);
			}
		}
		status = node->status;
		node = dequeue(queue);
	}
	print_signal_error(status, coredump);
}

void	destroy_exec(t_exec *exec)
{
	if (exec->commands)
		destroy_etree(exec->commands);
	if (exec->pipeline)
		destroy_queue(exec->pipeline, NULL);
	free(exec);
}
