/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internals.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:19:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/22 17:48:39 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNALS_H
# define PARSER_INTERNALS_H

# include "minishell.h"

char		**get_paths(char *envp[]);
char		*get_pathname(char *arg, char **path_list);
t_node		*main_pipeline(t_minishell *minishell);
t_command	*init_command(void);

// Builtins

t_bool		isbuiltin(char *arg);
void		configure_builtin(t_command *command);

#endif