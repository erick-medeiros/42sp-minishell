/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/15 15:40:05 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "architecture.h"
#include "minishell.h"
#include <stdlib.h>

t_node	*main_pipeline(t_minishell *minishell);

void	parser(t_minishell *minishell)
{
	minishell->command_table = malloc(sizeof(t_pipeline *) * 2);
	minishell->command_table[0] = malloc(sizeof(t_pipeline));
	minishell->command_table[0]->commands = main_pipeline(minishell);
	minishell->command_table[0]->logical_operator = LOGICAL_COMMAND;
	minishell->command_table[1] = NULL;
}

enum e_steps {
	PARSER_STEP_PATH,
	PARSER_STEP_ARG,
	PARSER_STEP_END
};

t_node	*main_pipeline(t_minishell *minishell)
{
	t_node		*list;
	t_node		*token;
	t_command	*cmd;
	int			steps;

	list = NULL;
	token = minishell->token_list;
	steps = PARSER_STEP_PATH;
	while (token)
	{
		if (steps == PARSER_STEP_PATH)
		{
			cmd = malloc(sizeof(t_command));
			cmd->pathname = (char *)token->content;
			cmd->args = malloc(sizeof(char *) * 1);
			cmd->args[0] = NULL;
			steps = PARSER_STEP_ARG;
		}
		else if (steps == PARSER_STEP_ARG)
		{
			free(cmd->args);
			cmd->args = malloc(sizeof(char *) * 3);
			cmd->args[0] = cmd->pathname;
			cmd->args[1] = (char *)token->content;
			cmd->args[2] = NULL;
		}
		token = token->next;
	}
	add_node(&list, cmd);
	return (list);
}
