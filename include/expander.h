/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:28:19 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/12 21:04:45 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

// Environment variable-related functions
int		cmp_vars_by_name(void *a, void *b);
void	envp_to_list(char **envp, t_vlst *vars);
char	**list_to_envp(t_vlst *vars, int quote);
t_var	*new_var_node_from_name_val(char *name, char *val);
t_var	*new_var_node_from_str(char *str);
int		split_name_val(char *str, char *equal_pos, t_var *content);
int		update_var(t_vlst *vars, t_var *content);
int		find_env_var(void *str, void *var);

// Expander

char	*expand_parameter(char *str, char *param_expand, t_minishell *ms);
char	*expand_variable(t_vlst *env_list, char *str);
char	*expand_filename(char *str);
char	*remove_quote(char *str);

// Utils
int		concat_expanded(char **str, int start, char *str_in, char *str_out);
char	*get_parameter_expansion(char *str);
char	*get_parameter(char *parameter_expansion);

char	*get_pathname(char *arg, char *envp[]);
char	**get_paths(char *envp[]);

#endif
