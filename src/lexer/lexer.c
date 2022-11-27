/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:31 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/26 18:12:39 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static t_lex_state	get_next_state(size_t idx, t_node **tokens,
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
	t_st_func		f;
	const t_st_func	state_funcs[] = {
		handle_amp_state, handle_and_state, handle_append_state,
		handle_brace_state, NULL, NULL, handle_cparenthesis_state,
		handle_dquote_state, handle_heredoc_state, NULL,
		handle_input_state, NULL, handle_oparenthesis_state,
		handle_or_state, handle_output_state, handle_pipe_state,
		handle_skip_state, handle_squote_state, handle_word_state
	};

	f = state_funcs[st];
	if (f != NULL)
		return (f(idx, tokens, vi));
	return (STATE_INVALID);
}
