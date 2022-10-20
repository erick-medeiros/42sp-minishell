/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:31 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/20 11:15:41 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static t_lex_state	get_next_state(char ch, t_node **tokens, t_lex_state st);

t_node	*lexer(char *prompt)
{
	t_node		*tokens;
	t_lex_state	next_state;

	next_state = STATE_START;
	while (next_state != STATE_COMPLETE && next_state != STATE_INCOMPLETE
		&& next_state != STATE_INCOMPLETE)
		next_state = get_next_state(*prompt++, &tokens, next_state);
	if (next_state != STATE_COMPLETE)
	{
		clear_list(tokens, del_token_node);
		return (NULL);
	}
	return (tokens);
}

static t_lex_state	get_next_state(char ch, t_node **tokens, t_lex_state st)
{
	if (st == STATE_START)
		return (handle_start_state(ch, tokens));
	else if (st == STATE_WORD)
		return (handle_word_state(ch, tokens));
	else if (st == STATE_SPACE)
		return (handle_space_state(ch, tokens));
	else if (st == STATE_DQUOTE)
		return (handle_dquote_state(ch, tokens));
	else if (st == STATE_INPUT)
		return (handle_input_state(ch, tokens));
	else if (st == STATE_OUTPUT)
		return (handle_output_state(ch, tokens));
	else if (st == STATE_PIPE)
		return (handle_pipe_state(ch, tokens));
	else if (st == STATE_APPEND)
		return (handle_append_state(ch, tokens));
	else if (st == STATE_SQUOTE)
		return (handle_squote_state(ch, tokens));
	else
		return (STATE_INVALID);
}
