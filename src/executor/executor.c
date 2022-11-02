/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 09:17:50 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtins.h"
#include "structs.h"

void	executor(t_minishell *minishell)
{
	t_node		*node;
	t_pipeline	*pipeline;

	node = minishell->pipelines;
	while (node)
	{
		pipeline = (t_pipeline *) node->content;
		if (pipeline->operator == OPERATOR_MAIN)
			tree_executor(minishell, pipeline);
		else if (pipeline->operator == OPERATOR_MAIN)
			pipeline_executor(minishell, pipeline);
		node = node->next;
	}
}

void	pipeline_executor(t_minishell *minishell, t_pipeline *pipeline)
{
	t_cmd	*cmd;
	t_node	*node;

	open_pipes(pipeline);
	node = pipeline->commands;
	while (node)
	{
		cmd = node->content;
		if (cmd->isbuiltin && !cmd->subshell)
			builtins(minishell, cmd);
		else
		{
			connect_pipes(pipeline, cmd);
			subshell(minishell, cmd);
		}
		node = node->next;
	}
	close_pipes(pipeline);
	node = pipeline->commands;
	while (node)
	{
		cmd = node->content;
		if (cmd->subshell)
		{
			waitpid(cmd->pid, &cmd->status, 0);
			process_exit_status(cmd);
			if (cmd->status != 0)
				panic_error(strerror(cmd->status));
		}
		node = node->next;
	}
}

void	builtins(t_minishell *minishell, t_cmd *command)
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
		destroy_minishell(minishell);
		builtin_exit();
	}
}
