/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:38:32 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 19:33:10 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

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
