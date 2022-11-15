/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:36:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/14 22:22:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "structs.h"
#include "parser.h"

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
	command->pipefd[READ_PIPE] = STDIN;
	command->pipefd[WRITE_PIPE] = STDOUT;
	command->pid = 0;
	command->status = 0;
	command->number = number;
	command->isbuiltin = FALSE;
	command->subshell = TRUE;
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
	free(command->argv);
	free(command->pathname);
	free_string_list(command->envp);
	free(command);
}

int	initialize_command(t_cmd *command)
{
	if (command->argc > 0)
	{
		if (isbuiltin(command->argv[0]))
		{
			command->isbuiltin = TRUE;
			configure_builtin(command);
			return (OK);
		}
	}
	return (OK);
}
