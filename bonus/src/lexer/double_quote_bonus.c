/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:20:40 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/06 15:27:30 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "lexer_bonus.h"

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
