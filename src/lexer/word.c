/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:22:50 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/28 19:50:43 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static t_lex_state	new_word_token(t_node **tokens,
						t_val_info *vi, t_lex_state next_state);

t_lex_state	handle_word_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->prompt[idx];

	if (next_ch == '|')
		return (new_word_token(tokens, vi, STATE_PIPE));
	if (next_ch == '>')
		return (new_word_token(tokens, vi, STATE_OUTPUT));
	if (next_ch == '<')
		return (new_word_token(tokens, vi, STATE_INPUT));
	if (next_ch == '"')
		return (new_word_token(tokens, vi, STATE_DQUOTE));
	if (next_ch == '\'')
		return (new_word_token(tokens, vi, STATE_SQUOTE));
	if (ft_isspace(next_ch))
		return (new_word_token(tokens, vi, STATE_SKIP));
	if (next_ch == '\0')
		return (new_word_token(tokens, vi, STATE_COMPLETE));
	vi->len++;
	return (STATE_WORD);
}

static t_lex_state	new_word_token(t_node **tokens,
	t_val_info *vi, t_lex_state next_state)
{
	if (new_token_with_val(tokens, TOKEN_WORD, vi))
		return (STATE_INVALID);
	return (next_state);
}
