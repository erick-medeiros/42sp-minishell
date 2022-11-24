/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:01:06 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/24 12:20:59 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_lex_state	handle_cparenthesis_state(size_t idx, t_node **tokens,
		t_val_info *vi)
{
	const char	next_ch = vi->line[idx];

	new_token(tokens, TOKEN_CPARENTHESIS);
	if (next_ch == '|')
		return (STATE_PIPE);
	if (lexer_parenthesis(next_ch) != STATE_SKIP)
		return (lexer_parenthesis(next_ch));
	if (next_ch == '>')
		return (STATE_OUTPUT);
	if (next_ch == '<')
		return (STATE_INPUT);
	if (next_ch == '&')
		return (STATE_AMPERSAND);
	if (ft_isspace(next_ch))
		return (STATE_SKIP);
	if (next_ch == '\0')
		return (STATE_COMPLETE);
	if (next_ch == '$')
		return (init_word_value(idx, vi, STATE_BRACE));
	if (next_ch == '"')
		return (init_word_value(idx, vi, STATE_DQUOTE));
	if (next_ch == '\'')
		return (init_word_value(idx, vi, STATE_SQUOTE));
	return (init_word_value(idx, vi, STATE_WORD));
}

t_lex_state	handle_oparenthesis_state(size_t idx, t_node **tokens,
		t_val_info *vi)
{
	const char	next_ch = vi->line[idx];

	new_token(tokens, TOKEN_OPARENTHESIS);
	if (next_ch == '|')
		return (STATE_PIPE);
	if (lexer_parenthesis(next_ch) != STATE_SKIP)
		return (lexer_parenthesis(next_ch));
	if (next_ch == '>')
		return (STATE_OUTPUT);
	if (next_ch == '<')
		return (STATE_INPUT);
	if (next_ch == '&')
		return (STATE_AMPERSAND);
	if (ft_isspace(next_ch))
		return (STATE_SKIP);
	if (next_ch == '\0')
		return (STATE_COMPLETE);
	if (next_ch == '$')
		return (init_word_value(idx, vi, STATE_BRACE));
	if (next_ch == '"')
		return (init_word_value(idx, vi, STATE_DQUOTE));
	if (next_ch == '\'')
		return (init_word_value(idx, vi, STATE_SQUOTE));
	return (init_word_value(idx, vi, STATE_WORD));
}

t_lex_state	lexer_parenthesis(char next_ch)
{
	if (next_ch == '(')
		return (STATE_OPARENTHESIS);
	if (next_ch == ')')
		return (STATE_CPARENTHESIS);
	return (STATE_SKIP);
}
