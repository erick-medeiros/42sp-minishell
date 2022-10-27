/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:31 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/27 02:53:21 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lex_state	get_next_state(size_t idx, t_node **tokens,
	t_lex_state st, t_val_info *vi);

int	lexer(char *prompt, t_node **tokens, t_lex_state start_state)
{
	t_lex_state	next_state;
	t_val_info	vi;
	size_t		idx;

	vi = (t_val_info){.start = 0, .len = 0, .prompt = prompt, .active = 0};
	idx = 0;
	next_state = start_state;
	while (next_state != STATE_COMPLETE && next_state != STATE_DQINCOMP
		&& next_state != STATE_SQINCOMP && next_state != STATE_INVALID)
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
	if (st == STATE_WORD)
		return (handle_word_state(idx, tokens, vi));
	if (st == STATE_SKIP)
		return (handle_skip_state(idx, vi));
	if (st == STATE_DQUOTE)
		return (handle_dquote_state(idx, tokens, vi));
	if (st == STATE_SQUOTE)
		return (handle_squote_state(idx, tokens, vi));
	if (st == STATE_INPUT)
		return (handle_input_state(idx, tokens, vi));
	if (st == STATE_OUTPUT)
		return (handle_output_state(idx, tokens, vi));
	if (st == STATE_PIPE)
		return (handle_pipe_state(idx, tokens, vi));
	if (st == STATE_APPEND)
		return (handle_append_state(idx, tokens, vi));
	if (st == STATE_HEREDOC)
		return (handle_heredoc_state(idx, tokens, vi));
	return (STATE_INVALID);
}
