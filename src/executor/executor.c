/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/22 19:13:56 by eandre-f         ###   ########.fr       */
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
		node->cmd.output = pipefd[WRITE_PIPE];
		node->next->cmd.input = pipefd[READ_PIPE];
		node->cmd.ispipeline = TRUE;
		node->next->cmd.ispipeline = TRUE;
	}
	if (node->group)
		group_executor(exec, env, node);
	else
		execute_command(exec, &node->cmd, env);
	close_safe(node->cmd.input);
	close_safe(node->cmd.output);
	enqueue(exec->pipeline, node);
	if (!node->next || node->next->operator != OP_PIPE)
		pipeline_sync(exec->pipeline);
	if (node->next && ((node->next->operator == OP_PIPE)
			|| (node->next->operator == OP_AND && node->cmd.status == 0)
			|| (node->next->operator == OP_OR && node->cmd.status != 0)))
		etree_executor(exec, env, node->next);
}

void	group_executor(t_exec *exec, t_vlst *env, t_etree *node)
{
	t_etree	*last;

	node->cmd.pid = fork();
	if (node->cmd.pid == 0)
	{
		node->group->cmd.input = node->cmd.input;
		last = node->group;
		while (last && last->next)
			last = last->next;
		last->cmd.output = node->cmd.output;
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
		if (node->cmd.pid > 0)
		{
			waitpid(node->cmd.pid, &node->cmd.status, 0);
			if (WIFEXITED(node->cmd.status))
				node->cmd.status = WEXITSTATUS(node->cmd.status);
			else if (WIFSIGNALED(node->cmd.status))
			{
				coredump = WCOREDUMP(node->cmd.status);
				node->cmd.status = 128 + WTERMSIG(node->cmd.status);
			}
		}
		status = node->cmd.status;
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
