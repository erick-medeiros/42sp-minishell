/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/22 17:50:58 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parser_internals.h"

void	parser(t_minishell *minishell)
{
	t_node		*list;
	t_pipeline	*pipeline;

	minishell->path_list = get_paths(minishell->envp);
	list = NULL;
	pipeline = malloc(sizeof(t_pipeline));
	pipeline->commands = main_pipeline(minishell);
	pipeline->command_count = 1;
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
	char		*tmp;

	list = NULL;
	node = minishell->token_list;
	steps = PARSER_STEP_PATH;
	cmd = init_command();
	while (node)
	{
		token = node->content;
		if (steps == PARSER_STEP_PATH)
		{
			cmd->number = 0;
			cmd->isbuiltin = isbuiltin(token->value);
			if (cmd->isbuiltin)
				cmd->pathname = ft_strdup(token->value);
			else
				cmd->pathname = get_pathname(token->value, minishell->path_list);
			cmd->argc = 1;
			cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
			cmd->argv[0] = ft_strdup(token->value);
			cmd->argv[1] = NULL;
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
		node = node->next;
	}
	configure_builtin(cmd);
	add_node(&list, cmd);
	return (list);
}

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->pathname = NULL;
	command->argc = 0;
	command->argv = NULL;
	command->input = STDIN;
	command->output = STDOUT;
	command->pid = 0;
	command->status = 0;
	command->number = 0;
	command->pipefds = NULL;
	command->isbuiltin = FALSE;
	command->subshell = TRUE;
	return (command);
}
