/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/19 19:15:31 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor_internals.h"

void	execute_commands(t_minishell *minishell, t_node *commands);
void	child_process(t_minishell *minishell, t_command *command);

void	executor(t_minishell *minishell)
{
	t_node		*node;
	t_pipeline	*pipeline;

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

	node = commands;
	while (node)
	{
		cmd = (t_command *) node->content;
		if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		{
			free_minishell(minishell);
			builtin_exit();
		}
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
		waitpid(cmd->pid, &cmd->exit_code, 0);
		if (WIFEXITED(cmd->exit_code))
			cmd->exit_code = WEXITSTATUS(cmd->exit_code);
		if (cmd->exit_code != 0)
			write(STDOUT, "Error", 5);
		node = node->next;
	}
}

void	child_process(t_minishell *minishell, t_command *command)
{
	char	*pathname;

	pathname = get_pathname(command->pathname, minishell->envp);
	if (pathname == NULL)
	{
		free_minishell(minishell);
		exit(0);
	}
	if (execve(pathname, command->args, minishell->envp) == -1)
		write(STDERR, "Error", 5);
}
