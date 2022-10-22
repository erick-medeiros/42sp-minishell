/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/22 16:29:17 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor_internals.h"

void	child_process(t_minishell *minishell, t_command *command)
{
	child_process_io(minishell, command);
	if (!command->pathname)
		exit_process(minishell, 127);
	if (execve(command->pathname, command->argv, minishell->envp) == -1)
		exit_process(minishell, errno);
	exit_process(minishell, 1);
}

void	child_process_io(t_minishell *minishell, t_command *command)
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
	free_minishell(minishell);
	clear_list(minishell->env_list.list, del_var_node);
	exit(status);
}

void	process_exit_status(t_command *command)
{
	if (WIFEXITED(command->status))
		command->status = WEXITSTATUS(command->status);
	if (command->status != 0)
		strerror(command->status);
}
