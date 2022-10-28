/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 19:19:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/28 19:45:00 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

char		*get_pathname(char *arg, char **path_list);
char		**get_paths(char *envp[]);
t_pipeline	*pipeline_generator(t_minishell *minishell);

// Builtins

t_bool		isbuiltin(char *arg);
void		configure_builtin(t_cmd *command);

#endif