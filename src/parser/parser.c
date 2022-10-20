/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/20 19:57:49 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

t_node		*main_pipeline(t_minishell *minishell);
t_bool		command_isbuiltin(char *arg0);
t_command	*init_command(void);

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
			cmd = init_command();
			cmd->pathname = ft_strdup(token->value);
			cmd->argc = 1;
			cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
			cmd->argv[0] = ft_strdup(cmd->pathname);
			cmd->argv[1] = NULL;
			steps = PARSER_STEP_ARG;
		}
		else if (steps == PARSER_STEP_ARG)
		{
			free_string_list(cmd->argv);
			cmd->argc = 2;
			cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
			cmd->argv[0] = ft_strdup(cmd->pathname);
			cmd->argv[1] = ft_strdup(token->value);
			cmd->argv[2] = NULL;
		}
		node = node->next;
	}
	cmd->isbuiltin = command_isbuiltin(cmd->pathname);
	add_node(&list, cmd);
	return (list);
}

t_bool	command_isbuiltin(char *arg0)
{
	if (ft_strcmp(arg0, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(arg0, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(arg0, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(arg0, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(arg0, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(arg0, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(arg0, "exit") == 0)
		return (TRUE);
	return (FALSE);
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
	command->isbuiltin = FALSE;
	return (command);
}
