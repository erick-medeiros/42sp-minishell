/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:36:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/31 19:31:42 by eandre-f         ###   ########.fr       */
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

t_cmd	*duplicate_command(t_cmd *command)
{
	t_cmd	*cmd;
	int		i;

	cmd = new_command(command->number);
	if (command->pathname)
		cmd->pathname = ft_strdup(command->pathname);
	cmd->pid = command->pid;
	cmd->status = command->status;
	cmd->envp = command->envp;
	cmd->argc = command->argc;
	cmd->input = command->input;
	cmd->output = command->output;
	cmd->subshell = command->subshell;
	cmd->isbuiltin = command->isbuiltin;
	cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
	i = 0;
	while (command->argv[i])
	{
		cmd->argv[i] = ft_strdup(command->argv[i]);
		++i;
	}
	cmd->argv[cmd->argc] = NULL;
	return (cmd);
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
