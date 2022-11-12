/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:24:50 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/12 02:28:44 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

t_lex_state	handle_append_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_brace_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_continue_state(t_node **tokens, t_val_info *vi);
t_lex_state	handle_dquote_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_heredoc_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_input_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_output_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_pipe_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_skip_state(size_t idx, t_val_info *vi);
t_lex_state	handle_squote_state(size_t idx, t_node **tokens, t_val_info *vi);
t_lex_state	handle_word_state(size_t idx, t_node **tokens, t_val_info *vi);
int			new_token(t_node **tokens, t_tok_type tok_type);
int			new_token_with_val(t_node **tokens, t_tok_type tok_type,
				t_val_info *vi);
t_lex_state	init_word_value(size_t idx, t_val_info *vi, t_lex_state st);
t_lex_state	init_quote_value(size_t idx, t_val_info *vi, t_lex_state st);
t_lex_state	new_word_token(t_node **tokens, t_val_info *vi,
				t_lex_state next_state);

#endif
