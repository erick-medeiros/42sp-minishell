/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/20 19:13:22 by eandre-f         ###   ########.fr       */
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
		if (cmd->isbuiltin)
			builtins(minishell, cmd);
		else
		{
			pathname = get_pathname(cmd->pathname, minishell->path_list);
			free(cmd->pathname);
			cmd->pathname = pathname;
			cmd->pid = fork();
			if (cmd->pid < 0)
				write(STDERR, "Error", 5);
			else if (cmd->pid == 0)
				child_process(minishell, cmd);
		}
		node = node->next;
	}
	node = commands;
	while (node)
	{
		cmd = (t_command *) node->content;
		if (!cmd->isbuiltin)
		{
			waitpid(cmd->pid, &cmd->status, 0);
			process_exit_status(cmd);
		}
		node = node->next;
	}
}

void	builtins(t_minishell *minishell, t_command *command)
{
	if (command_is_equal(command->pathname, "echo"))
	{
		if (command->argc == 3 && command_is_equal(command->argv[1], "-n"))
			builtin_echo("-n", command->argv[2]);
		else if (command->argc == 2)
			builtin_echo("", command->argv[1]);
	}
	else if (command_is_equal(command->pathname, "cd") && command->argc == 2)
		builtin_cd(command->argv[1], &minishell->env_list);
	else if (command_is_equal(command->pathname, "pwd"))
		builtin_pwd();
	else if (command_is_equal(command->pathname, "export"))
		builtin_export(command->argc, command->argv, &minishell->env_list);
	else if (command_is_equal(command->pathname, "unset"))
		builtin_unset(command->argc, command->argv, &minishell->env_list);
	else if (command_is_equal(command->pathname, "env"))
		builtin_env(&minishell->env_list);
	else if (command_is_equal(command->pathname, "exit"))
	{
		free_minishell(minishell);
		builtin_exit();
	}
}
