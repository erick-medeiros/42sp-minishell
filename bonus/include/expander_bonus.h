/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_bonus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:28:19 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 11:14:32 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <sys/stat.h>
# include "minishell_bonus.h"

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

char	*parameter_expansion(char *src, t_vlst *env);
char	*expand_parameter(char *str, int quote, t_vlst *env);
char	*expand_variable(char *str, t_vlst *env);
t_node	*expand_filename(t_tok_type tok_type, char *match);
char	*remove_quote(char *str);

// Utils
int		update_quote(char c, int quote);
char	*convert_list_to_string(t_node *list);
int		print_file_error(char *path, int error_number);

#endif
