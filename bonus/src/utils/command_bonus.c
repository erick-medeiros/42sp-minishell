/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:36:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/21 04:05:43 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
	command->pid = 0;
	command->status = 0;
	command->number = number;
	command->isbuiltin = FALSE;
	command->redirect = NULL;
	command->word_tokens = NULL;
	return (command);
}

void	destroy_command(t_cmd *command)
{
	int	i;

	if (command == NULL)
		return ;
	i = 0;
	while (command->argv && command->argv[i] && i < command->argc + 1)
		free(command->argv[i++]);
	clear_list(command->redirect, free_token);
	free(command->argv);
	free(command->pathname);
	free_string_list(command->envp);
	clear_list(command->word_tokens, free_token);
	free(command);
}
