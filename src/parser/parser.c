/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/25 10:04:56 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parser_internals.h"

void	parser(t_minishell *minishell)
{
	t_node		*list;
	t_pipeline	*pipeline;
	t_node		*node;

	list = NULL;
	pipeline = new_pipeline(OPERATOR_MAIN);
	pipeline->commands = main_pipeline(minishell);
	pipeline->command_count = 0;
	node = pipeline->commands;
	while (node)
	{
		pipeline->command_count++;
		node = node->next;
	}
	add_node(&list, pipeline);
	minishell->pipelines = list;
}

enum e_steps {
	PARSER_STEP_EXEC,
	PARSER_STEP_ARG,
	PARSER_STEP_END
};

t_node	*main_pipeline(t_minishell *minishell)
{
	t_node		*list;
	t_node		*node;
	t_cmd		*cmd;
	t_token		*token;
	int			steps;
	char		*tmp;
	int			number;

	list = NULL;
	steps = PARSER_STEP_EXEC;
	node = minishell->token_list;
	cmd = NULL;
	number = 0;
	while (node)
	{
		token = node->content;
		if (token->type == TOKEN_PIPE)
			steps = PARSER_STEP_END;
		if (steps == PARSER_STEP_EXEC)
		{
			cmd = new_command();
			cmd->number = number++;
			cmd->isbuiltin = isbuiltin(token->value);
			if (cmd->isbuiltin)
				cmd->pathname = ft_strdup(token->value);
			else
				cmd->pathname = get_pathname(token->value, minishell->path_list);
			cmd->argc = 1;
			cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
			cmd->argv[0] = ft_strdup(token->value);
			cmd->argv[1] = NULL;
			configure_builtin(cmd);
			steps = PARSER_STEP_ARG;
		}
		else if (steps == PARSER_STEP_ARG)
		{
			tmp = ft_strdup(cmd->argv[0]);
			free_string_list(cmd->argv);
			cmd->argc = 2;
			cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
			cmd->argv[0] = tmp;
			cmd->argv[1] = ft_strdup(token->value);
			cmd->argv[2] = NULL;
		}
		else if (steps == PARSER_STEP_END)
		{
			add_node(&list, cmd);
			steps = PARSER_STEP_EXEC;
		}
		node = node->next;
	}
	if (steps == PARSER_STEP_ARG)
		steps = PARSER_STEP_END;
	if (steps == PARSER_STEP_END)
		add_node(&list, cmd);
	return (list);
}
