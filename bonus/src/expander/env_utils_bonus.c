/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:03:07 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/06 15:19:00 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	str_to_name_val_node(char *str, char *equal_pos, t_var *content)
{
	size_t	len;

	len = (size_t)(equal_pos - str);
	content->name = malloc(sizeof(char) * (len + 1));
	if (!content->name)
		return (ERR_ALLOC);
	ft_strlcpy(content->name, str, len + 1);
	len = ft_strlen(equal_pos + 1);
	content->val = malloc(sizeof(char) * (len + 1));
	if (!content->val)
	{
		free(content->name);
		return (ERR_ALLOC);
	}
	ft_strlcpy(content->val, equal_pos + 1, len + 1);
	return (OK);
}

t_var	*new_var_node_from_str(char *str)
{
	t_var	*content;
	char	*equal_pos;

	if (!str)
		return (NULL);
	equal_pos = ft_strchr(str, '=');
	if (!equal_pos)
		return (NULL);
	content = malloc(sizeof(*content));
	if (!content)
		return (NULL);
	if (str_to_name_val_node(str, equal_pos, content))
	{
		free(content);
		return (NULL);
	}
	return (content);
}

t_var	*new_var_node_from_name_val(char *name, char *val)
{
	t_var	*content;

	if (!name)
		return (NULL);
	content = malloc(sizeof(*content));
	if (!content)
		return (NULL);
	content->name = ft_strdup(name);
	if (val == NULL)
		content->val = NULL;
	else
		content->val = ft_strdup(val);
	return (content);
}

int	cmp_vars_by_name(void *a, void *b)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (!a && !b)
		return (0);
	if (!b)
		return (1);
	if (!a)
		return (-1);
	s1 = (unsigned char *)((t_var *)a)->name;
	s2 = (unsigned char *)((t_var *)b)->name;
	if (!s1 && !s2)
		return (0);
	if (!s2)
		return (1);
	if (!s1)
		return (-1);
	while (*s1 == *s2
		&& *s1 != '\0')
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	update_var(t_vlst *vars, t_var *content)
{
	t_node_funcs	funcs;

	funcs.clear = del_var_node;
	funcs.cmp = cmp_vars_by_name;
	if (!vars || !content)
		return (ERR_NOT_FOUND);
	if (change_node_content(vars->list, content,
			content, &funcs))
	{
		if (add_node(&(vars->list), content))
		{
			del_var_node(content);
			return (ERR_ALLOC);
		}
		vars->len++;
	}
	return (OK);
}
