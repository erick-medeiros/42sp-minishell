/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:19:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/12 23:52:21 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define MSG_SYNTAX_ERR "minishell: syntax error near unexpected token `|'"
# define MSG_ALLOC_ERR "minishell: allocation error"

typedef enum e_mode {
	IN_MODE,
	OUT_MODE,
	APPEND_MODE,
}	t_mode;

// Builtins

t_bool		isbuiltin(char *arg);
void		configure_builtin(t_cmd *command);

// Utils
int			print_parse_error(int parse_result);
int			open_fd(char *pathname, int mode);

int			new_op_node(t_tree	**op_node, t_tree_type op_type);
t_tree		*new_cmd_node(int num);
int			is_op(t_tree_type t);

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
