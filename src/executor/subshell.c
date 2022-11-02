/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 20:17:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expansor.h"
#include "builtins.h"
#include "structs.h"

void	subshell(t_minishell *minishell, t_cmd *command)
{
	command->pid = fork();
	if (command->pid < 0)
		panic_error("executor: fork");
	else if (command->pid == 0)
	{
		command->input = dup(command->input);
		command->output = dup(command->output);
		close_pipeline(minishell->root);
		subshell_redirect(minishell, command);
		if (command->isbuiltin)
			execute_builtin(minishell, command);
		else
			execute_program(minishell, command);
		exit_subshell(minishell, 1);
	}
}

void	execute_builtin(t_minishell *minishell, t_cmd *command)
{
	if (command_is_equal(command->pathname, "echo"))
		builtin_echo(command);
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
	if (command->subshell)
		exit_subshell(minishell, 0);
}

void	execute_program(t_minishell *minishell, t_cmd *command)
{
	command->envp = list_to_envp(&minishell->env_list, 0);
	free(command->pathname);
	command->pathname = get_pathname(command->argv[0], command->envp);
	if (!command->pathname)
		exit_subshell(minishell, 127);
	if (execve(command->pathname, command->argv, command->envp) == -1)
		exit_subshell(minishell, errno);
}

void	subshell_redirect(t_minishell *minishell, t_cmd *command)
{
	dup2(command->input, STDIN);
	dup2(command->output, STDOUT);
	if (command->input > STDERR)
		close(command->input);
	if (command->output > STDERR)
		close(command->output);
	if (command->redirect_input)
	{
		command->input = open_redirects(command->redirect_input);
		if (command->input == -1)
			exit_subshell(minishell, errno);
		dup2(command->input, STDIN);
		if (command->input > STDERR)
			close(command->input);
	}
	if (command->redirect_output)
	{
		command->output = open_redirects(command->redirect_output);
		if (command->output == -1)
			exit_subshell(minishell, errno);
		dup2(command->output, STDOUT);
		if (command->output > STDERR)
			close(command->output);
	}
}

void	exit_subshell(t_minishell *minishell, int status)
{
	destroy_minishell(minishell);
	exit(status);
}
