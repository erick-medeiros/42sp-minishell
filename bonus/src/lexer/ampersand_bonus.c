/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 04:17:32 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/06 15:19:33 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "lexer_bonus.h"

t_lex_state	handle_amp_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char			next_ch = vi->line[idx];
	const t_val_info	amp_vi = (t_val_info){"&", 0, 1, 0};

	if (next_ch == '&')
		return (STATE_AND);
	new_token_with_val(tokens, TOKEN_WORD, (t_val_info *)&amp_vi);
	if (next_ch == '>')
		return (STATE_OUTPUT);
	if (next_ch == '|')
		return (STATE_PIPE);
	if (lexer_parenthesis(next_ch) != STATE_SKIP)
		return (lexer_parenthesis(next_ch));
	if (next_ch == '<')
		return (STATE_INPUT);
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
