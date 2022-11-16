/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:28:19 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 21:04:42 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34

// Environment variable-related functions
int		cmp_vars_by_name(void *a, void *b);
void	envp_to_list(char **envp, t_vlst *vars);
char	**list_to_envp(t_vlst *vars, size_t *len, int export);
t_var	*new_var_node_from_name_val(char *name, char *val);
t_var	*new_var_node_from_str(char *str);
int		update_var(t_vlst *vars, t_var *content);
int		find_env_var(void *str, void *var);

// Expander

char	*expand_parameter(char *str, t_minishell *ms);
char	*expand_variable(t_vlst *env_list, char *str);
char	*expand_filename(char *str);
char	*remove_quote(char *str);

// Utils
int		concat_expanded(char **str, int start, char *expanded);
char	*get_parameter_expansion(char *str);
char	*get_parameter(char *parameter_expansion);
int		update_quote(char c, int quote);

#endif
