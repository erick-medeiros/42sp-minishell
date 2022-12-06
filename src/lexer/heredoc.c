/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 02:35:57 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/06 17:08:03 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_lex_state	handle_heredoc_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->line[idx];

	if (new_token(tokens, TOKEN_HEREDOC))
		return (STATE_INVALID);
	if (next_ch == '|')
		return (STATE_PIPE);
	if (next_ch == '>')
		return (STATE_OUTPUT);
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
