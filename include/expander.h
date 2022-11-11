/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:28:19 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/09 01:25:31 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

// Environment variable-related functions
int			cmp_vars_by_name(void *a, void *b);
void		envp_to_list(char **envp, t_vlst *vars);
char		**list_to_envp(t_vlst *vars, int quote);
t_var		*new_var_node_from_name_val(char *name, char *val);
t_var		*new_var_node_from_str(char *str);
int			split_name_val(char *str, char *equal_pos, t_var *content);
int			update_var(t_vlst *vars, t_var *content);
int			find_env_var(void *str, void *var);

// Path

char		*get_pathname(char *arg, char *envp[]);
char		**get_paths(char *envp[]);

char		*clean_quote_expander(char *str);

#endif