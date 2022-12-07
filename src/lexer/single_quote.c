/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:22:19 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/07 12:53:49 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_lex_state	handle_squote_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->line[idx];

	if (next_ch == '\0')
	{
		if (vi->in_braces)
		{
			if (new_token_with_val(tokens, TOKEN_SQBRACE, vi))
				return (STATE_INVALID);
			return (STATE_INCOMPLETE);
		}
		if (new_token_with_val(tokens, TOKEN_SQINCOMP, vi))
			return (STATE_INVALID);
		return (STATE_INCOMPLETE);
	}
	vi->len++;
	if (next_ch == '\'')
		return (STATE_WORD);
	return (STATE_SQUOTE);
}
