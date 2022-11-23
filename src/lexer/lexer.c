/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:31 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/23 12:09:44 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static t_lex_state	get_next_state(size_t idx, t_node **tokens,
						t_lex_state st, t_val_info *vi);
static t_lex_state	get_next_state2(size_t idx, t_node **tokens,
						t_lex_state st, t_val_info *vi);

int	lexer(char **line, t_node **tokens, t_lex_state st)
{
	t_lex_state	next_state;
	t_val_info	vi;
	size_t		idx;

	vi.start = 0;
	vi.len = 0;
	vi.line = *line;
	vi.in_braces = FALSE;
	if (st == STATE_CONTINUE)
	{
		next_state = handle_continue_state(tokens, &vi);
		*line = vi.line;
	}
	else
		next_state = st;
	idx = vi.len;
	while (next_state != STATE_COMPLETE && next_state != STATE_INCOMPLETE
		&& next_state != STATE_INVALID)
		next_state = get_next_state(idx++, tokens, next_state, &vi);
	if (next_state == STATE_INVALID)
	{
		clear_list(*tokens, del_token_node);
		return (ERR_LEXER);
	}
	return (OK);
}

static t_lex_state	get_next_state(size_t idx, t_node **tokens,
	t_lex_state st, t_val_info *vi)
{
	if (st == STATE_AMPERSAND)
		return (handle_amp_state(idx, tokens, vi));
	if (st == STATE_AND)
		return (handle_and_state(idx, tokens, vi));
	if (st == STATE_APPEND)
		return (handle_append_state(idx, tokens, vi));
	if (st == STATE_OR)
		return (handle_or_state(idx, tokens, vi));
	if (st == STATE_WORD)
		return (handle_word_state(idx, tokens, vi));
	if (st == STATE_SKIP)
		return (handle_skip_state(idx, tokens, vi));
	if (st == STATE_DQUOTE)
		return (handle_dquote_state(idx, tokens, vi));
	if (st == STATE_SQUOTE)
		return (handle_squote_state(idx, tokens, vi));
	if (st == STATE_BRACE)
		return (handle_brace_state(idx, tokens, vi));
	if (st == STATE_INPUT)
		return (handle_input_state(idx, tokens, vi));
	if (st == STATE_OUTPUT)
		return (handle_output_state(idx, tokens, vi));
	return (get_next_state2(idx, tokens, st, vi));
}

static t_lex_state	get_next_state2(size_t idx, t_node **tokens,
	t_lex_state st, t_val_info *vi)
{
	if (st == STATE_PIPE)
		return (handle_pipe_state(idx, tokens, vi));
	if (st == STATE_APPEND)
		return (handle_append_state(idx, tokens, vi));
	if (st == STATE_HEREDOC)
		return (handle_heredoc_state(idx, tokens, vi));
	return (STATE_INVALID);
}
