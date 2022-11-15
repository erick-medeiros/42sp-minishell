/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 18:40:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expander.h"
#include "builtins.h"
#include "structs.h"

void	subshell(t_minishell *minishell, t_cmd *command)
{
	int	status;

	handle_signal(SIGINT, command_signal_handler);
	handle_signal(SIGQUIT, command_signal_handler);
	command->pid = fork();
	if (command->pid < 0)
		panic_error("executor: fork");
	else if (command->pid == 0)
	{
		subshell_redirect(command);
		close_pipeline(minishell->root);
		status = 0;
		if (command->isbuiltin)
			status = execute_builtin(minishell, command);
		else
			status = execute_program(command);
		destroy_minishell(minishell);
		exit(status);
	}
}

int	execute_builtin(t_minishell *minishell, t_cmd *command)
{
	if (ft_streq(command->argv[0], "echo"))
		builtin_echo(command);
	else if (ft_streq(command->argv[0], "cd") && command->argc == 2)
		builtin_cd(command->argv[1], &minishell->env_list);
	else if (ft_streq(command->argv[0], "pwd"))
		builtin_pwd();
	else if (ft_streq(command->argv[0], "export"))
		builtin_export(command->argc, command->argv, &minishell->env_list);
	else if (ft_streq(command->argv[0], "unset"))
		builtin_unset(command->argc, command->argv, &minishell->env_list);
	else if (ft_streq(command->argv[0], "env"))
		builtin_env(&minishell->env_list);
	else if (ft_streq(command->argv[0], "exit"))
	{
		destroy_minishell(minishell);
		builtin_exit();
	}
	if (command->status == 2)
	{
		ft_putstr_fd(command->argv[0], STDERR);
		ft_putendl_fd(": misuse of shell builtins", STDERR);
	}
	return (0);
}

int	execute_program(t_cmd *command)
{
	if (!command->pathname)
	{
		ft_putstr_fd(command->argv[0], STDERR);
		ft_putendl_fd(": command not found", STDERR);
		return (127);
	}
	if (access(command->pathname, X_OK) != 0)
	{
		ft_putstr_fd(command->argv[0], STDERR);
		ft_putendl_fd(": command invoked cannot execute", STDERR);
		return (126);
	}
	errno = 0;
	execve(command->pathname, command->argv, command->envp);
	if (errno)
		perror(command->argv[0]);
	return (1);
}

void	subshell_redirect(t_cmd *command)
{
	dup2(command->piping[READ_PIPE], STDIN);
	dup2(command->piping[WRITE_PIPE], STDOUT);
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
