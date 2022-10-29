/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internals.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:19:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/25 10:05:16 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNALS_H
# define PARSER_INTERNALS_H

# include "minishell.h"

char		*get_pathname(char *arg, char **path_list);
t_node		*main_pipeline(t_minishell *minishell);

// Builtins

t_bool		isbuiltin(char *arg);
void		configure_builtin(t_cmd *command);

// New and destroy

t_cmd		*new_command(void);
void		destroy_command(t_cmd *command);
t_pipeline	*new_pipeline(t_operator operator);
void		destroy_pipeline(t_pipeline	*pipeline);

#endif