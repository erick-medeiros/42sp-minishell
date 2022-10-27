/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:20:40 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/27 12:32:36 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex_state	handle_dquote_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->prompt[idx];

	if (vi->active == 0)
		init_word_value(idx, vi, STATE_DQUOTE);
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
