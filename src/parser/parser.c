/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/28 13:43:23 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parser_internals.h"

void	parser_add_arg_cmd(t_cmd *cmd, char *arg);

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

typedef enum e_steps {
	STEP_PATH,
	STEP_ARG,
	STEP_END
}	t_steps;

t_node	*main_pipeline(t_minishell *minishell)
{
	t_node		*list;
	t_node		*node;
	t_cmd		*cmd;
	t_token		*token;
	t_steps		step;
	int			number;

	list = NULL;
	step = STEP_PATH;
	node = minishell->token_list;
	cmd = NULL;
	number = 0;
	while (node)
	{
		token = node->content;
		if (step == STEP_PATH)
		{
			if (token->type != TOKEN_WORD)
				panic_error("error parser STEP_PATH");
			if (!cmd)
				cmd = new_command(number++);
			cmd->isbuiltin = isbuiltin(token->value);
			if (!cmd->isbuiltin)
				cmd->pathname = get_pathname(token->value, minishell->path_list);
			parser_add_arg_cmd(cmd, token->value);
			configure_builtin(cmd);
			step = STEP_ARG;
		}
		else if (step == STEP_ARG)
		{
			if (token->type == TOKEN_WORD)
				parser_add_arg_cmd(cmd, token->value);
			else if (token->type == TOKEN_PIPE)
				step = STEP_END;
			else
				panic_error("error parser STEP_ARG");
		}
		if (step == STEP_END)
		{
			add_node(&list, cmd);
			cmd = NULL;
			step = STEP_PATH;
		}
		node = node->next;
	}
	if (step == STEP_ARG || step == STEP_END)
		add_node(&list, cmd);
	return (list);
}

void	parser_add_arg_cmd(t_cmd *cmd, char *arg)
{
	char	**temp;
	int		i;

	temp = cmd->argv;
	cmd->argc++;
	cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
	i = 0;
	while (temp && temp[i])
	{
		cmd->argv[i] = ft_strdup(temp[i]);
		++i;
	}
	cmd->argv[i] = ft_strdup(arg);
	cmd->argv[cmd->argc] = NULL;
	free_string_list(temp);
}
