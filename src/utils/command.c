/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:36:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/16 21:04:31 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content);

t_cmd	*new_command(int number)
{
	t_cmd	*command;

	command = malloc(sizeof(t_cmd));
	command->pathname = NULL;
	command->argc = 0;
	command->argv = NULL;
	command->envp = NULL;
	command->input = STDIN;
	command->output = STDOUT;
	command->piping[READ_PIPE] = STDIN;
	command->piping[WRITE_PIPE] = STDOUT;
	command->pid = 0;
	command->status = 0;
	command->number = number;
	command->isbuiltin = FALSE;
	command->redirect = NULL;
	return (command);
}

void	destroy_command(t_cmd *command)
{
	int	i;

	if (command == NULL)
		return ;
	i = 0;
	while (command->argv && i < command->argc + 1)
	{
		free(command->argv[i]);
		++i;
	}
	if (command->redirect)
	{
		clear_list(command->redirect, free_token);
		command->redirect = NULL;
	}
	free(command->argv);
	free(command->pathname);
	free_string_list(command->envp);
	free(command);
}
