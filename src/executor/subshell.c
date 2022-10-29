/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/27 18:37:52 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor_internals.h"

void	subshell(t_minishell *minishell, t_pipeline *pipeline, t_cmd *command)
{
	connect_pipes(pipeline, command);
	command->pid = fork();
	if (command->pid < 0)
		panic_error("executor: fork");
	else if (command->pid == 0)
	{
		command->input = dup(command->input);
		command->output = dup(command->output);
		close_pipes(pipeline);
		update_io(minishell, command);
		if (command->isbuiltin)
		{
			builtins(minishell, command);
			exit_process(minishell, 0);
		}
		else
			child_process(minishell, command);
	}
}

void	child_process(t_minishell *minishell, t_cmd *command)
{
	char	**envp;

	envp = list_to_envp(&minishell->env_list, 0);
	if (!command->pathname)
		exit_process(minishell, 127);
	if (execve(command->pathname, command->argv, envp) == -1)
		exit_process(minishell, errno);
	exit_process(minishell, 1);
}

void	update_io(t_minishell *minishell, t_cmd *command)
{
	if (command->input < 0 || command->output < 0)
	{
		if (command->input >= 0)
			close(command->input);
		if (command->output >= 0)
			close(command->output);
		exit_process(minishell, 1);
	}
	dup2(command->input, STDIN);
	dup2(command->output, STDOUT);
	close(command->input);
	close(command->output);
}

void	exit_process(t_minishell *minishell, int status)
{
	destroy_minishell(minishell);
	exit(status);
}

void	process_exit_status(t_cmd *command)
{
	if (WIFEXITED(command->status))
		command->status = WEXITSTATUS(command->status);
}