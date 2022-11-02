/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/01 19:58:58 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expansor.h"
#include "builtins.h"

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
	builtins(minishell, command);
	exit_subshell(minishell, 0);
}

void	execute_program(t_minishell *minishell, t_cmd *command)
{
	char	**envp;
	char	*pathname;

	envp = list_to_envp(&minishell->env_list, 0);
	minishell->path_list = get_paths(envp);
	pathname = command->pathname;
	command->pathname = get_pathname(pathname, minishell->path_list);
	free(pathname);
	if (!command->pathname)
		exit_subshell(minishell, 127);
	if (execve(command->pathname, command->argv, envp) == -1)
		exit_subshell(minishell, errno);
}

void	subshell_redirect(t_minishell *minishell, t_cmd *command)
{
	if (command->input < 0 || command->output < 0)
	{
		if (command->input >= 0)
			close(command->input);
		if (command->output >= 0)
			close(command->output);
		exit_subshell(minishell, 1);
	}
	dup2(command->input, STDIN);
	dup2(command->output, STDOUT);
	close(command->input);
	close(command->output);
}

void	exit_subshell(t_minishell *minishell, int status)
{
	destroy_minishell(minishell);
	exit(status);
}

void	process_exit_status(t_cmd *command)
{
	if (WIFEXITED(command->status))
		command->status = WEXITSTATUS(command->status);
}
