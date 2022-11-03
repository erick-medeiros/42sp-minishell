/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:19:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/03 02:11:33 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define MSG_SYNTAX_ERR "minishell: syntax error near unexpected token `|'"

typedef enum e_mode {
	IN_MODE,
	OUT_MODE,
	APPEND_MODE,
}	t_mode;

t_pipeline	*pipeline_generator(t_minishell *minishell);

// Builtins

t_bool		isbuiltin(char *arg);
void		configure_builtin(t_cmd *command);

// Utils
int			print_parse_error(int parse_result);
int			open_fd(char *pathname, int mode);

// Heredoc
int			process_heredoc(t_node **heredoc_queue);

// Tree

t_tree		*convert_list_to_tree(t_pipeline *pipeline);

// Token parsing
int			handle_word_token(t_token *tok, t_tree *cmd_node, t_minishell *ms);
int			handle_redirect_token(t_node **tokens, t_tree *cmd_node,
				t_minishell *ms);
int			enqueue_heredoc(t_node **heredoc_queue, t_tree *cmd_node,
				t_minishell *ms);

// Variable expansion
int			expand_filename(char *src, char **dst, t_minishell *ms);
int			expand_vars(char *src, char **dst, t_minishell *ms);

#endif
