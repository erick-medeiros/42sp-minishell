/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_internals.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:24:50 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/28 19:27:14 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_INTERNALS_H
# define LEXER_INTERNALS_H

# include "minishell.h"

typedef enum e_lex_state {
	STATE_APPEND,
	STATE_COMPLETE,
	STATE_DQUOTE,
	STATE_DQINCOMP,
	STATE_HEREDOC,
	STATE_INPUT,
	STATE_INVALID,
	STATE_OUTPUT,
	STATE_PIPE,
	STATE_SKIP,
	STATE_SQUOTE,
	STATE_SQINCOMP,
	STATE_WORD
}	t_lex_state;

typedef struct s_val_info
{
	char	*prompt;
	size_t	start;
	size_t	len;
	int		active;
}	t_val_info;

t_lex_state	handle_append_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_dquote_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_heredoc_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_input_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_output_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_pipe_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_skip_state(size_t idx, t_val_info *vi);
t_lex_state	handle_squote_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_word_state(size_t idx, t_node **tokens, t_val_info *vi);
int			lexer(char *prompt, t_node **tokens, t_lex_state start_state);
int			new_token(t_node **tokens, t_tok_type tok_type);
int			new_token_with_val(t_node **tokens, t_tok_type tok_type,
				t_val_info *vi);
t_lex_state	init_word_value(size_t idx, t_val_info *vi, t_lex_state st);
t_lex_state	init_quote_value(size_t idx, t_val_info *vi, t_lex_state st);

#endif