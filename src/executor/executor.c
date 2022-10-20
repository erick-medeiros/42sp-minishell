/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/20 12:27:26 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor_internals.h"

void	execute_commands(t_minishell *minishell, t_node *commands);

void	executor(t_minishell *minishell)
{
	t_node		*node;
	t_pipeline	*pipeline;

	minishell->path_list = get_paths(minishell->envp);
	node = minishell->pipelines;
	while (node)
	{
		pipeline = (t_pipeline *) node->content;
		if (pipeline->operator == OPERATOR_MAIN)
			execute_commands(minishell, pipeline->commands);
		node = node->next;
	}
}

void	execute_commands(t_minishell *minishell, t_node *commands)
{
	t_node		*node;
	t_command	*cmd;
	char		*pathname;

	node = commands;
	while (node)
	{
		cmd = (t_command *) node->content;
		if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		{
			free_minishell(minishell);
			builtin_exit();
		}
		pathname = get_pathname(cmd->pathname, minishell->path_list);
		free(cmd->pathname);
		cmd->pathname = pathname;
		cmd->pid = fork();
		if (cmd->pid < 0)
			write(STDERR, "Error", 5);
		else if (cmd->pid == 0)
			child_process(minishell, cmd);
		else
			node = node->next;
	}
	node = commands;
	while (node)
	{
		cmd = (t_command *) node->content;
		waitpid(cmd->pid, &cmd->status, 0);
		process_exit_status(cmd);
		node = node->next;
	}
}
