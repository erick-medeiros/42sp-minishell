/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:19:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/18 00:36:36 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// Utils

int			new_op_node(t_tree	**op_node, t_tree_type op_type);
t_tree		*new_cmd_node(int num);
int			is_op(t_tree_type t);
int			print_token_error(int status, t_tok_type tok_type);

// postfix list utils

int			push_postfix(t_node **tmp_stack, t_queue *cmds, t_tree *tree);
int			flush_postfix(t_node **tmp_stack, t_queue *cmds);

// Heredoc

void		process_heredoc(t_queue *heredoc_queue);

// Tree

t_tree		*build_tree_postfix(t_minishell *ms);

// Token parsing

int			handle_next_token(t_tree *cmd_node, t_minishell *ms);
int			handle_word_token(t_tree *cmd_node, t_minishell *ms);
int			handle_redirect_token(t_tree *cmd_node, t_minishell *ms);
int			enqueue_heredoc(t_tree *cmd_node, t_minishell *ms);

#endif
