/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:38:32 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/11 02:35:21 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

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
