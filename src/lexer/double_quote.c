/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:20:40 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/28 19:50:15 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_lex_state	handle_dquote_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->prompt[idx];

	if (vi->active == 0)
	{
		init_word_value(idx, vi, STATE_DQUOTE);
		return (STATE_DQUOTE);
	}
	if (next_ch == '"')
	{
		if (new_token_with_val(tokens, TOKEN_DQUOTE, vi))
			return (STATE_INVALID);
		return (STATE_SKIP);
	}
	if (next_ch == '\0')
	{
		if (new_token_with_val(tokens, TOKEN_DQINCOMP, vi))
			return (STATE_INVALID);
		return (STATE_DQINCOMP);
	}
	vi->len++;
	return (STATE_DQUOTE);
}
