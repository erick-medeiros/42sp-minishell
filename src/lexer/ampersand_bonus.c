/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 04:17:32 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/20 04:24:46 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "structs.h"

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
