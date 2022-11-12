/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:20:40 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/12 04:15:27 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "structs.h"

t_lex_state	handle_dquote_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->line[idx];

	if (next_ch == '\0')
	{
		if (vi->in_braces)
		{
			if (new_token_with_val(tokens, TOKEN_DQBRACE, vi))
				return (STATE_INVALID);
			return (STATE_INCOMPLETE);
		}
		if (new_token_with_val(tokens, TOKEN_DQINCOMP, vi))
			return (STATE_INVALID);
		return (STATE_INCOMPLETE);
	}
	vi->len++;
	if (next_ch == '"')
		return (STATE_WORD);
	return (STATE_DQUOTE);
}
