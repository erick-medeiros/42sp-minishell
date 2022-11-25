/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:17:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/25 11:19:26 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_tree_type	tok_to_tree_type(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
		return (TREE_TYPE_PIPE);
	if (tok->type == TOKEN_AND)
		return (TREE_TYPE_AND);
	if (tok->type == TOKEN_OR)
		return (TREE_TYPE_OR);
	if (tok->type == TOKEN_OPARENTHESIS)
		return (TREE_TYPE_OPAR);
	if (tok->type == TOKEN_CPARENTHESIS)
		return (TREE_TYPE_CPAR);
	return (TREE_TYPE_CMD);
}

int	is_op(t_tree_type t)
{
	return (t != TREE_TYPE_CMD);
}

int	is_optoken(t_token *token)
{
	if (token->type == TOKEN_PIPE)
		return (TRUE);
	if (token->type == TOKEN_AND)
		return (TRUE);
	if (token->type == TOKEN_OR)
		return (TRUE);
	return (FALSE);
}

t_tree	*new_cmd_node(int num)
{
	t_tree	*cmd_node;

	(void)num;
	cmd_node = malloc(sizeof(*cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = TREE_TYPE_CMD;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	cmd_node->content = new_command();
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
