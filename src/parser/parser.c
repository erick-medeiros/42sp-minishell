/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 18:50:48 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parser.h"

typedef enum e_mode {
	IN_MODE,
	OUT_MODE,
	APPEND_MODE,
}	t_mode;

void	parser_add_arg_cmd(t_cmd *cmd, char *arg);
int		open_fd(char *pathname, int mode);

int	parser(t_minishell *minishell, t_node **heredoc_queue)
{
	t_node		*list;
	t_pipeline	*pipeline;

	(void)heredoc_queue;
	list = NULL;
	pipeline = pipeline_generator(minishell);
	add_node(&list, pipeline);
	minishell->pipelines = list;
	return (OK);
}

typedef enum e_steps {
	STEP_PATH,
	STEP_ARG,
	STEP_END
}	t_steps;

t_pipeline	*pipeline_generator(t_minishell *minishell)
{
	t_pipeline	*pipeline;
	t_node		*node;
	t_cmd		*cmd;
	t_token		*token;
	t_steps		step;

	pipeline = new_pipeline(OPERATOR_MAIN);
	step = STEP_PATH;
	node = minishell->token_list;
	cmd = NULL;
	while (node)
	{
		token = node->content;
		if (step == STEP_PATH)
		{
			if (token->type != TOKEN_WORD)
				panic_error("error parser STEP_PATH");
			if (!cmd)
				cmd = new_command(pipeline->command_count++);
			cmd->isbuiltin = isbuiltin(token->value);
			cmd->pathname = ft_strdup(token->value);
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
			add_node(&pipeline->commands, cmd);
			cmd = NULL;
			step = STEP_PATH;
		}
		node = node->next;
	}
	if (step == STEP_ARG || step == STEP_END)
		add_node(&pipeline->commands, cmd);
	return (pipeline);
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

int	open_fd(char *pathname, int mode)
{
	int	fd;
	int	permissions;

	permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (mode == IN_MODE)
		fd = open(pathname, O_RDONLY);
	else if (mode == OUT_MODE)
		fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, permissions);
	else if (mode == APPEND_MODE)
		fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, permissions);
	else
		fd = open(pathname, O_RDWR | O_WRONLY | O_CREAT | O_TRUNC, permissions);
	return (fd);
}

t_tree	*insert_into_tree(t_tree *root, t_tree_type type, void *content)
{
	t_tree	*temp;
	t_tree	*current;
	t_tree	*parent;

	(void) parent;
	temp = new_tree_node(type);
	temp->content = content;
	if (root == NULL)
		root = temp;
	else
	{
		current = root;
		parent = NULL;
		if (current->type == TREE_TYPE_PIPE && current->right == NULL)
		{
			current->right = temp;
		}
		else
		{
			root = temp;
			root->left = current;
		}
	}
	return (root);
}

t_tree	*convert_list_to_tree(t_pipeline *pipeline)
{
	t_tree	*root;
	t_node	*list;

	root = NULL;
	list = pipeline->commands;
	while (list)
	{
		root = insert_into_tree(root, TREE_TYPE_CMD, list->content);
		list->content = NULL;
		list = list->next;
		if (list)
			root = insert_into_tree(root, TREE_TYPE_PIPE, NULL);
	}
	return (root);
}
