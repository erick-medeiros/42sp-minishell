/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:59:25 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/06 02:26:38 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static char	*copy_to_str(t_var *content, int quote);

char	**list_to_envp(t_vlst *vars, int quote)
{
	char	**envp;
	char	**cur_str;
	t_node	*cur_node;

	envp = malloc(sizeof(*envp) * (vars->len + 1));
	if (!envp)
		return (NULL);
	cur_str = envp;
	cur_node = vars->list;
	while (cur_node)
	{
		*cur_str = copy_to_str(cur_node->content, quote);
		if (!(*cur_str))
			return (clear_envp(envp));
		cur_node = cur_node->next;
		cur_str++;
	}
	envp[vars->len] = NULL;
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

static char	*copy_to_str(t_var *content, int quote)
{
	size_t	name_len;
	size_t	val_len;
	char	*str;

	name_len = ft_strlen(content->name);
	val_len = ft_strlen(content->val);
	str = malloc(sizeof(*str) * (name_len + val_len + quote * 2 + 2));
	if (!str)
		return (NULL);
	ft_strlcpy(str, content->name, name_len + 1);
	str[name_len] = '=';
	if (quote)
		str[name_len + 1] = '"';
	ft_strlcpy(str + name_len + quote + 1, content->val, val_len + 1);
	if (quote)
	{
		str[name_len + val_len + 2] = '"';
		str[name_len + val_len + 3] = '\0';
	}
	return (str);
}
