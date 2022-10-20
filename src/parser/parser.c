/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/20 12:19:39 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*main_pipeline(t_minishell *minishell);

void	parser(t_minishell *minishell)
{
	t_node		*list;
	t_pipeline	*pipeline;

	list = NULL;
	pipeline = malloc(sizeof(t_pipeline));
	pipeline->commands = main_pipeline(minishell);
	pipeline->operator = OPERATOR_MAIN;
	add_node(&list, pipeline);
	minishell->pipelines = list;
}

enum e_steps {
	PARSER_STEP_PATH,
	PARSER_STEP_ARG,
	PARSER_STEP_END
};

t_node	*main_pipeline(t_minishell *minishell)
{
	t_node		*list;
	t_node		*node;
	t_command	*cmd;
	t_token		*token;
	int			steps;

	list = NULL;
	node = minishell->token_list;
	steps = PARSER_STEP_PATH;
	while (node)
	{
		token = node->content;
		if (steps == PARSER_STEP_PATH)
		{
			cmd = malloc(sizeof(t_command));
			cmd->pathname = ft_strdup(token->value);
			cmd->args = malloc(sizeof(char *) * 2);
			cmd->args[0] = ft_strdup(cmd->pathname);
			cmd->args[1] = NULL;
			cmd->input = STDIN;
			cmd->output = STDOUT;
			steps = PARSER_STEP_ARG;
		}
		else if (steps == PARSER_STEP_ARG)
		{
			free(cmd->args[0]);
			free(cmd->args[1]);
			free(cmd->args);
			cmd->args = malloc(sizeof(char *) * 3);
			cmd->args[0] = ft_strdup(cmd->pathname);
			cmd->args[1] = ft_strdup(token->value);
			cmd->args[2] = NULL;
		}
		node = node->next;
	}
	add_node(&list, cmd);
	return (list);
}
