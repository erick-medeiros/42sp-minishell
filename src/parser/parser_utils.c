/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:57:23 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/04 21:12:00 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	get_command(t_node **tokens, t_tree **cmd_node,
		t_minishell *ms, int num)
{
	int result;

	if (*tokens == NULL)
		return (OK);
	*cmd_node = new_cmd_node(num);
	if (!(*cmd_node))
		return (ERR_ALLOC);
	while (*tokens != NULL)
	{
		result = handle_next_token(tokens, *cmd_node, ms);
		if (result != OK)
			return (result);
		*tokens = remove_node(*tokens, del_token_node);
	}
	return (OK);
}

int	handle_next_token(t_node **tokens, t_tree *cmd_node,
				t_minishell *ms)
{
	t_token	*tok;

	tok = ((t_token *)(*tokens)->content);
	if (tok->type == TOKEN_PIPE)
		return (OK);
	if (tok->type == TOKEN_WORD)
		return (handle_word_token(tok, cmd_node, ms));
	if (tok->type == TOKEN_INPUT || tok->type == TOKEN_OUTPUT
		|| tok->type == TOKEN_APPEND)
		return (handle_redirect_token(tokens, cmd_node, ms));
	if (tok->type == TOKEN_HEREDOC)
		return (enqueue_heredoc(tokens, cmd_node, ms));
	if (tok->type == TOKEN_DQINCOMP)
		return (ERR_INCOMP_DQ);
	if (tok->type == TOKEN_SQINCOMP)
		return (ERR_INCOMP_SQ);
	return (ERR_BAD_SYNTAX);
}

t_tree	*new_cmd_node(int num)
{
	t_tree *cmd_node;
	cmd_node = malloc(sizeof(*cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = TREE_TYPE_CMD;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	cmd_node->content = new_command(num);
	return (cmd_node);
}

int	new_op_node(t_tree	**op_node, t_tree_type op_type)
{

	*op_node = malloc(sizeof(**op_node));
	if (!op_node)
		return (ERR_ALLOC);
	(*op_node)->type = op_type;
	(*op_node)->left = NULL;
	(*op_node)->right = NULL;
	(*op_node)->content = NULL;
	return (OK);
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
