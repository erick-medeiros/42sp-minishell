/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:22:19 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/28 19:50:36 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "lexer.h"

t_lex_state	handle_squote_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->prompt[idx];

	if (vi->active == 0)
	{
		init_word_value(idx, vi, STATE_SQUOTE);
		return (STATE_SQUOTE);
	}
	if (next_ch == '\'')
	{
		if (new_token_with_val(tokens, TOKEN_SQUOTE, vi))
			return (STATE_INVALID);
		return (STATE_SKIP);
	}
	if (next_ch == '\0')
	{
		if (new_token_with_val(tokens, TOKEN_SQINCOMP, vi))
			return (STATE_INVALID);
		return (STATE_SQINCOMP);
	}
	vi->len++;
	return (STATE_SQUOTE);
}
