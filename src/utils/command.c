/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:36:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 10:41:33 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

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
	while (command->argv && command->argv[i])
	{
		free(command->argv[i]);
		++i;
	}
	free(command->argv);
	free(command->pathname);
	free_string_list(command->envp);
	free(command);
}

t_pipeline	*new_pipeline(t_operator operator)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	pipeline->command_count = 0;
	pipeline->operator = operator;
	pipeline->pipefds = NULL;
	pipeline->commands = NULL;
	return (pipeline);
}

void	destroy_pipeline(t_pipeline	*pipeline)
{
	if (pipeline == NULL)
		return ;
	if (pipeline->commands)
		clear_list(pipeline->commands, (void (*)(void *))destroy_command);
	free(pipeline);
}
