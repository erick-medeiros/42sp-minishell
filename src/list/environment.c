/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:03:07 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/12 14:00:30 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vlst	envp_to_list(char **envp, t_vlst *vars)
{
	t_var	*content;

	vars->list = NULL;
	vars->len = 0;
	while (envp)
	{
		content = new_var_node(*envp++);
		if (!content || !add_node(&(vars->list), content))
		{
			clear_list(vars->list, del_var_node);
			vars->len = 0;
			return (*vars);
		}
		vars->len++;
	}
	return (*vars);
}

int	split_name_val(char *str, char *equal_pos, t_var *content)
{
	size_t	len;

	len = (size_t)(equal_pos - str);
	content->name = malloc(sizeof(char) * (len + 1));
	if (!content->name)
	{
		free(content);
		return (ERR_ALLOC);
	}
	ft_strlcpy(content->name, str, len);
	content->name[len] = '\0';
	len = ft_strlen(equal_pos + 1);
	content->val = malloc(sizeof(char) * (len + 1));
	if (!content->val)
	{
		free(content->name);
		free(content);
		return (ERR_ALLOC);
	}
	ft_strlcpy(content->val, equal_pos + 1, len);
	content->val[len] = '\0';
	return (OK);
}

t_var	*new_var_node(char *str)
{
	t_var	*content;
	char	*equal_pos;

	content = malloc(sizeof(*content));
	equal_pos = ft_strchr(str, '=');
	if (!content || !equal_pos)
		return (NULL);
	if (split_name_val(str, equal_pos, content))
		return (NULL);
	return (content);
}

char	**list_to_envp(t_vlst *vars)
{
	char	**envp;
	char	**cur_str;
	t_node	*cur_node;
	size_t	name_len;
	size_t	val_len;

	envp = malloc(sizeof(*envp) * (vars->len + 1));
	if (!envp)
		return (NULL);
	cur_str = envp;
	cur_node = vars->list;
	while (cur_node)
	{
		name_len = ft_strlen(((t_var *)cur_node->content)->name);
		val_len = ft_strlen(((t_var *)cur_node->content)->val);
		*cur_str = malloc(sizeof(**cur_str) * (name_len + val_len + 2));
		if (!cur_str)
			return (clear_envp(envp));
		ft_strlcpy(*cur_str, ((t_var *)cur_node->content)->name, name_len);
		*cur_str[name_len] = '=';
		ft_strlcpy(*cur_str++, ((t_var *)cur_node->content)->val, val_len + 1);
		cur_node++;
	}
	envp[vars->len] = NULL;
	return (envp);
}

int	cmp_vars_by_name(void *a, void *b)
{
	const char	*s1 = ((t_var *)a)->name;
	const char	*s2 = ((t_var *)b)->name;

	if (!s1 && !s2)
		return (0);
	if (!s2)
		return (1);
	if (!s1)
		return (-1);
	while (*s1 == *(unsigned char *)s2
		&& *(unsigned char *)s1 != '\0')
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
