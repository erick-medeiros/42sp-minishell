/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:56:27 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/12 04:15:16 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "structs.h"

static t_lex_state	set_val_info(t_lex_state st, t_val_info *vi, t_bool braces);

t_lex_state	handle_continue_state(t_node **tokens, t_val_info *vi)
{
	t_lex_state	state;

	if (((t_token *)(*tokens)->content)->type == TOKEN_DQINCOMP)
		state = set_val_info(STATE_DQUOTE, vi, FALSE);
	else if (((t_token *)(*tokens)->content)->type == TOKEN_SQINCOMP)
		state = set_val_info(STATE_SQUOTE, vi, FALSE);
	else if (((t_token *)(*tokens)->content)->type == TOKEN_DQBRACE)
		state = set_val_info(STATE_DQUOTE, vi, TRUE);
	else if (((t_token *)(*tokens)->content)->type == TOKEN_SQBRACE)
		state = set_val_info(STATE_SQUOTE, vi, TRUE);
	else if (((t_token *)(*tokens)->content)->type == TOKEN_BRCINCOMP)
		state = set_val_info(STATE_WORD, vi, TRUE);
	else
		state = STATE_INVALID;
	vi->len = ft_strlen(((t_token *)(*tokens)->content)->value);
	ft_strappend(&((t_token *)(*tokens)->content)->value, vi->line);
	free(vi->line);
	vi->line = ((t_token *)(*tokens)->content)->value;
	((t_token *)(*tokens)->content)->value = NULL;
	*tokens = remove_node(*tokens, del_token_node);
	return (state);
}

static t_lex_state	set_val_info(t_lex_state st, t_val_info *vi, t_bool braces)
{
	vi->in_braces = braces;
	return (st);
}
