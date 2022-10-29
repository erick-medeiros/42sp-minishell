/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 02:35:57 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/28 19:50:18 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

t_lex_state	handle_heredoc_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->prompt[idx];

	if (new_token(tokens, TOKEN_HEREDOC))
		return (STATE_INVALID);
	if (next_ch == '|')
		return (STATE_PIPE);
	if (next_ch == '>')
		return (STATE_OUTPUT);
	if (next_ch == '<')
		return (STATE_INPUT);
	if (next_ch == '"')
		return (STATE_DQUOTE);
	if (next_ch == '\'')
		return (STATE_SQUOTE);
	if (ft_isspace(next_ch))
		return (STATE_SKIP);
	if (next_ch == '\0')
		return (STATE_COMPLETE);
	return (init_word_value(idx, vi, STATE_WORD));
}
