/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:38:32 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/16 14:07:58 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

# define ERR_BUILTIN 2
# define MSG_PWD_ERR "Error: get working directory failed\n"
# define MSG_PATH_MAX_ERR "Error: path max buffer\n"
# define MSG_PWD_ALLOC_ERR "Error: memory cannot be allocated\n"

// Builtins

int		builtin_cd(char *path, t_vlst *vars);
int		builtin_echo(t_cmd *command);
int		builtin_env(t_vlst *vars);
void	builtin_exit(int status, t_minishell *ms, t_cmd *cmd);
int		builtin_export(int argc, char *argv[], t_vlst *vars);
int		builtin_pwd(void);
int		builtin_unset(int argc, char *argv[], t_vlst *vars);
char	*get_pwd(void);
t_bool	is_valid_name(char *name);

#endif
