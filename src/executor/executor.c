/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/22 17:06:48 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor_internals.h"

void	executor(t_minishell *minishell)
{
	t_node		*node;
	t_pipeline	*pipeline;

	node = minishell->pipelines;
	while (node)
	{
		pipeline = (t_pipeline *) node->content;
		if (pipeline->operator == OPERATOR_MAIN)
			pipeline_executor(minishell, pipeline);
		node = node->next;
	}
}

void	pipeline_executor(t_minishell *minishell, t_pipeline *pipeline)
{
	t_command	*command;
	t_node		*node;

	open_pipes(pipeline);
	node = pipeline->commands;
	while (node)
	{
		command = (t_command *) node->content;
		command->pipefds = pipeline->pipefds;
		run_command(minishell, pipeline, command);
		node = node->next;
	}
	close_pipes(pipeline);
	node = pipeline->commands;
	while (node)
	{
		command_exit_status(node->content);
		node = node->next;
	}
}

void	run_command(t_minishell *minishell, t_pipeline *pipeline,
			t_command *command)
{
	if (command->isbuiltin && command_is_equal(command->pathname, "exit"))
		builtins(minishell, command);
	command->pid = fork();
	if (command->pid < 0)
		panic_error("executor: fork");
	else if (command->pid == 0)
	{
		connect_pipes(pipeline, command);
		command->input = dup(command->input);
		command->output = dup(command->output);
		close_pipes(pipeline);
		if (command->isbuiltin)
		{
			child_process_io(minishell, command);
			builtins(minishell, command);
			exit_process(minishell, 0);
		}
		else
			child_process(minishell, command);
	}
}

void	command_exit_status(t_command *command)
{
	waitpid(command->pid, &command->status, 0);
	process_exit_status(command);
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
		clear_list(minishell->env_list.list, del_var_node);
		builtin_exit();
	}
}
