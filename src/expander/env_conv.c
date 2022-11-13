/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:59:25 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/12 22:22:19 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "structs.h"

static char	*copy_to_str(t_var *content, int export);
static char	*copy_to_str_null_val(t_var *content);

char	**list_to_envp(t_vlst *vars, size_t *len, int export)
{
	char	**envp;
	t_node	*cur_node;
	size_t	idx;

	envp = malloc(sizeof(*envp) * (vars->len + 1));
	if (!envp)
		return (NULL);
	idx = 0;
	cur_node = vars->list;
	while (cur_node)
	{
		if (export || ((t_var *)cur_node->content)->val != NULL)
		{
			envp[idx] = copy_to_str(cur_node->content, export);
			if (envp[idx] == NULL)
				return (clear_envp(envp));
			idx++;
		}
		cur_node = cur_node->next;
	}
	envp[idx] = NULL;
	if (len)
		*len = idx;
	return (envp);
}

void	envp_to_list(char **envp, t_vlst *vars)
{
	t_var	*content;

	vars->list = NULL;
	vars->len = 0;
	while (*envp)
	{
		content = new_var_node_from_str(*envp++);
		if (!content || add_node(&(vars->list), content))
		{
			clear_list(vars->list, del_var_node);
			vars->len = 0;
			return ;
		}
		vars->len++;
	}
	return ;
}

static char	*copy_to_str(t_var *content, int export)
{
	size_t	name_len;
	size_t	val_len;
	char	*str;

	if (content->val == NULL)
		return (copy_to_str_null_val(content));
	name_len = ft_strlen(content->name);
	val_len = ft_strlen(content->val);
	str = malloc(sizeof(*str) * (name_len + val_len + export * 2 + 2));
	if (!str)
		return (NULL);
	ft_strlcpy(str, content->name, name_len + 1);
	str[name_len] = '=';
	if (export)
		str[name_len + 1] = '"';
	ft_strlcpy(str + name_len + export + 1, content->val, val_len + 1);
	if (export)
	{
		str[name_len + val_len + 2] = '"';
		str[name_len + val_len + 3] = '\0';
	}
	return (str);
}

static char	*copy_to_str_null_val(t_var *content)
{
	size_t	name_len;
	char	*str;

	name_len = ft_strlen(content->name);
	str = malloc(sizeof(*str) * (name_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, content->name, name_len + 1);
	return (str);
}
