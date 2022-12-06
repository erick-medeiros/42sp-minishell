/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:17:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 15:21:40 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "parser_bonus.h"

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
	return (token->type == TOKEN_PIPE || token->type == TOKEN_AND
		|| token->type == TOKEN_OR);
}

t_bool	is_redir_token(t_tok_type t)
{
	return (t == TOKEN_INPUT || t == TOKEN_OUTPUT
		|| t == TOKEN_APPEND || t == TOKEN_HEREDOC);
}
