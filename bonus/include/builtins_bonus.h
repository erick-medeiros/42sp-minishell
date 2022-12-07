/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:38:32 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/07 15:20:53 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_BONUS_H
# define BUILTINS_BONUS_H

# include "minishell_bonus.h"

// Builtins

int		builtin_cd(int argc, char *argv[], t_vlst *vars);
int		builtin_echo(int fd_out, char *argv[]);
int		builtin_env(int fd_out, t_vlst *vars);
void	builtin_exit(t_exec *exec, int status);
void	builtin_exit_arg(t_exec *exec, int argc, char *argv[]);
int		builtin_export(int argc, char *argv[], t_vlst *vars);
int		builtin_pwd(int fd_out);
int		builtin_unset(int argc, char *argv[], t_vlst *vars);

#endif
