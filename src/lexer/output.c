/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:21:39 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/28 19:50:31 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "lexer.h"

t_lex_state	handle_output_state(size_t idx, t_node **tokens, t_val_info *vi)
{
	const char	next_ch = vi->prompt[idx];

	if (next_ch == '>')
		return (STATE_APPEND);
	new_token(tokens, TOKEN_OUTPUT);
	if (next_ch == '|')
		return (STATE_PIPE);
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
