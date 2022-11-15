/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/14 22:28:43 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expander.h"
#include "builtins.h"
#include "structs.h"

void	subshell(t_minishell *minishell, t_cmd *command)
{
	handle_signal(SIGINT, command_signal_handler);
	handle_signal(SIGQUIT, command_signal_handler);
	command->pid = fork();
	if (command->pid < 0)
		panic_error("executor: fork");
	else if (command->pid == 0)
	{
		subshell_redirect(command);
		close_pipeline(minishell->root);
		if (command->isbuiltin)
			execute_builtin(minishell, command);
		else
			execute_program(minishell, command);
		exit_subshell(minishell, 1);
	}
}

void	execute_builtin(t_minishell *minishell, t_cmd *command)
{
	if (command_is_equal(command->argv[0], "echo"))
		builtin_echo(command);
	else if (command_is_equal(command->argv[0], "cd") && command->argc == 2)
		builtin_cd(command->argv[1], &minishell->env_list);
	else if (command_is_equal(command->argv[0], "pwd"))
		builtin_pwd();
	else if (command_is_equal(command->argv[0], "export"))
		builtin_export(command->argc, command->argv, &minishell->env_list);
	else if (command_is_equal(command->argv[0], "unset"))
		builtin_unset(command->argc, command->argv, &minishell->env_list);
	else if (command_is_equal(command->argv[0], "env"))
		builtin_env(&minishell->env_list);
	else if (command_is_equal(command->argv[0], "exit"))
	{
		destroy_minishell(minishell);
		builtin_exit();
	}
	if (command->subshell)
		exit_subshell(minishell, 0);
}

void	execute_program(t_minishell *minishell, t_cmd *command)
{
	command->envp = list_to_envp(&minishell->env_list, NULL, 0);
	free(command->pathname);
	command->pathname = get_pathname(command->argv[0], command->envp);
	if (!command->pathname)
		exit_subshell(minishell, 127);
	if (execve(command->pathname, command->argv, command->envp) == -1)
		exit_subshell(minishell, errno);
}

void	subshell_redirect(t_cmd *command)
{
	dup2(command->pipefd[READ_PIPE], STDIN);
	dup2(command->pipefd[WRITE_PIPE], STDOUT);
	dup2(command->input, STDIN);
	dup2(command->output, STDOUT);
	if (command->input > STDERR)
		close(command->input);
	if (command->output > STDERR)
		close(command->output);
}

void	exit_subshell(t_minishell *minishell, int status)
{
	destroy_minishell(minishell);
	exit(status);
}
