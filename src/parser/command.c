/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:57:23 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/03 01:50:50 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static t_tree	*new_cmd_node(int num);
static int	handle_next_token(t_node **tokens, t_tree *cmd_node,
				t_minishell *ms);

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

static int	handle_next_token(t_node **tokens, t_tree *cmd_node,
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
	if (tok->type == TOKEN_DQINCOMP || tok->type == TOKEN_SQINCOMP)
		return (ERR_INCOMPLETE);
	return (ERR_BAD_TOKEN);
}

static t_tree	*new_cmd_node(int num)
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
