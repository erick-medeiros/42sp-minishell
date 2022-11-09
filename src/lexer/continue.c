/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 03:56:27 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/09 04:10:44 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "structs.h"

t_lex_state	handle_continue_state(t_node **tokens, t_val_info *vi)
{
	t_lex_state	state;

	if (((t_token *)(*tokens)->content)->type == TOKEN_DQINCOMP)
		state = STATE_DQUOTE;
	else if (((t_token *)(*tokens)->content)->type == TOKEN_SQINCOMP)
		state = STATE_SQUOTE;
	else
		state = STATE_INVALID;
	vi->len = ft_strlen(((t_token *)(*tokens)->content)->value);
	ft_strappend(&((t_token *)(*tokens)->content)->value, vi->prompt);
	// free(vi->prompt);
	vi->prompt = ((t_token *)(*tokens)->content)->value;
	((t_token *)(*tokens)->content)->value = NULL;
	*tokens = remove_node(*tokens, del_token_node);
	return (state);
}
