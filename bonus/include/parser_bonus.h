/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:19:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 15:23:58 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell_bonus.h"

// Utils

int			new_op_node(t_tree	**op_node, t_tree_type op_type);
t_tree		*new_cmd_node(void);
int			is_op(t_tree_type t);
int			is_optoken(t_token *token);
t_bool		is_redir_token(t_tok_type t);
int			print_token_error(int status, t_token *tok);
t_tree_type	tok_to_tree_type(t_token *tok);
int			validate_line_start(t_ms *ms);
int			handle_next_token_error(t_ms *ms);
int			handle_close_parenthesis(t_ms *ms, t_tree_type tree_type,
				t_tree **tree);

// postfix list utils

int			push_postfix(t_node **tmp_stack, t_queue *cmds, t_tree *tree);
int			flush_postfix(t_node **tmp_stack, t_queue *cmds);

// Heredoc

int			process_heredoc(t_token *token, char *delimiter, t_vlst *env);
int			heredoc(char *delimiter, t_vlst *env, t_bool *interrupted);

// Tree

t_tree		*build_tree_postfix(t_ms *ms);

// Token parsing

int			handle_next_token(t_tree *cmd_node, t_ms *ms);
int			handle_word_token(t_tree *cmd_node, t_ms *ms);
int			handle_redirect_token(t_tree *cmd_node, t_ms *ms);
int			enqueue_heredoc(t_tree *cmd_node, t_ms *ms);
int			handle_group_redirect_token(t_tree *group_node, t_ms *ms);

// Validation
int			validate_tokens(t_node	*cur_node);

#endif
