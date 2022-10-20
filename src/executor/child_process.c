/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/20 12:26:37 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor_internals.h"

void	child_process(t_minishell *minishell, t_command *command)
{
	if (command->input < 0 || command->output < 0)
		exit_process(minishell, 1);
	dup2(command->input, STDIN);
	dup2(command->output, STDOUT);
	if (!command->pathname)
		exit_process(minishell, 127);
	if (execve(command->pathname, command->args, minishell->envp) == -1)
		exit_process(minishell, errno);
	exit_process(minishell, 1);
}

void	exit_process(t_minishell *minishell, int status)
{
	free_minishell(minishell);
	exit(status);
}

void	process_exit_status(t_command *command)
{
	if (WIFEXITED(command->status))
		command->status = WEXITSTATUS(command->status);
	if (command->status != 0)
		strerror(command->status);
}
