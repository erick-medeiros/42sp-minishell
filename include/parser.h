/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:19:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 18:49:32 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define MSG_SYNTAX_ERR "minishell: syntax error near unexpected token `|'"

t_pipeline	*pipeline_generator(t_minishell *minishell);

// Builtins

t_bool		isbuiltin(char *arg);
void		configure_builtin(t_cmd *command);

// Utils
void		print_parse_error(int parse_result);

// Heredoc
int			process_heredoc(t_node **heredoc_queue);

// Tree

t_tree		*convert_list_to_tree(t_pipeline *pipeline);

#endif
