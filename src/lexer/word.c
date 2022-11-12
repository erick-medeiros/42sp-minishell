/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:22:50 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/12 04:13:42 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "structs.h"

static t_lex_state	handle_word_state_braces(const char next_ch,
						t_node **tokens, t_val_info *vi);

t_lex_state	handle_word_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->line[idx];

	if (vi->in_braces)
		return (handle_word_state_braces(next_ch, tokens, vi));
	if (next_ch == '\0')
		return (new_word_token(tokens, vi, STATE_COMPLETE));
	vi->len++;
	if (next_ch == '$')
		return (STATE_BRACE);
	if (next_ch == '"')
		return (STATE_DQUOTE);
	if (next_ch == '\'')
		return (STATE_SQUOTE);
	return (STATE_WORD);
}

static t_lex_state	handle_word_state_braces(const char next_ch,
	t_node **tokens, t_val_info *vi)
{
	if (next_ch == '|')
		return (new_word_token(tokens, vi, STATE_PIPE));
	if (next_ch == '>')
		return (new_word_token(tokens, vi, STATE_OUTPUT));
	if (next_ch == '<')
		return (new_word_token(tokens, vi, STATE_INPUT));
	if (ft_isspace(next_ch))
		return (new_word_token(tokens, vi, STATE_SKIP));
	if (next_ch == '\0')
	{
		if (new_token_with_val(tokens, TOKEN_BRCINCOMP, vi))
			return (STATE_INVALID);
		return (STATE_INCOMPLETE);
	}
	if (next_ch == '}')
		vi->in_braces = FALSE;
	vi->len++;
	if (next_ch == '"')
		return (STATE_DQUOTE);
	if (next_ch == '\'')
		return (STATE_SQUOTE);
	return (STATE_WORD);
}
