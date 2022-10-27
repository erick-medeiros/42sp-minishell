/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:22:00 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/27 02:32:51 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex_state	handle_pipe_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->prompt[idx];

	new_token(tokens, TOKEN_PIPE);
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
	init_word_value(idx, vi, STATE_WORD);
	return (STATE_WORD);
}