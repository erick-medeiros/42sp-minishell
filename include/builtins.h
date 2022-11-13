/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:38:32 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/13 01:26:57 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define MSG_PWD_ERR "Error: get working directory failed\n"
# define MSG_PATH_MAX_ERR "Error: path max buffer\n"
# define MSG_PWD_ALLOC_ERR "Error: memory cannot be allocated\n"

// Builtins

void		builtin_cd(char *path, t_vlst *vars);
void		builtin_echo(t_cmd *command);
void		builtin_env(t_vlst *vars);
void		builtin_exit(void);
void		builtin_export(int argc, char *argv[], t_vlst *vars);
void		builtin_pwd(void);
void		builtin_unset(int argc, char *argv[], t_vlst *vars);
char		*get_pwd(void);
t_bool		is_valid_name(char *name);

#endif
