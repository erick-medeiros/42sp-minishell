/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:20:40 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/10 00:56:16 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_lex_state	handle_dquote_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->line[idx];

	if (next_ch == '\0')
	{
		if (new_token_with_val(tokens, TOKEN_DQINCOMP, vi))
			return (STATE_INVALID);
		return (STATE_DQINCOMP);
	}
	vi->len++;
	if (next_ch == '"')
		return (STATE_WORD);
	return (STATE_DQUOTE);
}
