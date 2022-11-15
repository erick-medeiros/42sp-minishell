/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:51:42 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/15 13:44:09 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "minishell.h"
#include "expander.h"
#include "structs.h"

void	print_sorted_vars(t_vlst *vars, char *prefix)
{
	char	**envp;
	char	**tmp;
	size_t	len;

	envp = list_to_envp(vars, &len, 1);
	quicksort(envp, 0, len - 1);
	tmp = envp;
	while (*envp)
		printf("%s%s\n", prefix, *envp++);
	clear_envp(tmp);
}

int	change_or_create_var(t_vlst *vars, char *name, char *val)
{
	t_var	*content;
	int		result;

	content = new_var_node_from_name_val(name, val);
	if (!content)
		return (ERR_ALLOC);
	if (val != NULL)
	{
		result = update_var(vars, content);
		if (result != OK)
			return (result);
		vars->len++;
	}
	else if (!find_node_by_content(vars->list, content, cmp_vars_by_name))
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

int	split_name_val(char *str, char **name, char **val)
{
	char	*equal_pos;
	size_t	len;

	equal_pos = ft_strchr(str, '=');
	if (!equal_pos)
	{
		*name = ft_strdup(str);
		*val = NULL;
		if (*name == NULL)
			return (ERR_ALLOC);
		return (OK);
	}
	*name = malloc(sizeof(char) * ((size_t)(equal_pos - str) + 1));
	len = ft_strlen(equal_pos + 1);
	*val = malloc(sizeof(char) * (len + 1));
	if (*name == NULL || *val == NULL)
	{
		free(*name);
		return (ERR_ALLOC);
	}
	ft_strlcpy(*name, str, (size_t)(equal_pos - str) + 1);
	ft_strlcpy(*val, equal_pos + 1, len + 1);
	return (OK);
}

t_bool	is_valid_name(char *name)
{
	if (name == NULL || (*name != '_' && !ft_isalpha(*name)))
		return (FALSE);
	while (*(++name) != '\0')
	{
		if (*name != '_' && !ft_isalpha(*name) && !ft_isdigit(*name))
			return (FALSE);
	}
	return (TRUE);
}

void	init_system_vars(t_minishell *ms)
{
	int		shlvl;
	t_var	content;
	t_node	*node;
	char	*s;

	content.name = "SHLVL";
	content.val = NULL;
	node = find_node_by_content(ms->env_list.list, &content, cmp_vars_by_name);
	if (node != NULL)
	{
		shlvl = ft_atoi(((t_var *)node->content)->val);
		s = ft_itoa(shlvl + 1);
		change_or_create_var(&(ms->env_list), "SHLVL", s);
		free(s);
	}
}
