/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:52:31 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/12 05:22:44 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"
#include "minishell.h"

static void	change_or_create_var(t_vlst *vars, char *name, char *val);
static void	print_sorted_vars(t_vlst *vars, char *prefix);
static void	error_invalid_id(char * id);

void	builtin_export(int argc, char *argv[], t_vlst *vars)
{
	int		idx;
	char	*name;
	char	*val;

	if (argc == 1)
	{
		print_sorted_vars(vars, " declare - x ");
		return ;
	}
	idx = 1;
	while (idx < argc)
	{
		split_name_val(argv[idx], &name, &val);
		if (!is_valid_name(name))
		{
			error_invalid_id(argv[idx]);
			continue ;
		}
		change_or_create_var(vars, name, val);
	}
}

static void	print_sorted_vars(t_vlst *vars, char *prefix)
{
	char	**envp;
	char	**tmp;

	envp = list_to_envp(vars, 1);
	quicksort(envp, 0, vars->len - 1);
	tmp = envp;
	while (*envp)
		printf("%s%s\n", prefix, *envp++);
	clear_envp(tmp);
}

static void	change_or_create_var(t_vlst *vars, char *name, char *val)
{
	t_var			*content;
	t_node_funcs	funcs;

	funcs.clear = del_var_node;
	funcs.cmp = cmp_vars_by_name;
	content = new_var_node_from_name_val(name, val);
	if (!content)
		return ;
	if (change_node_content(vars->list, content, content, &funcs))
	{
		if (add_node(&(vars->list), content))
		{
			del_var_node(content);
			return ;
		}
		vars->len++;
	}
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
	ft_strlcpy(*name, str, (size_t)(equal_pos - str)+ 1);
	ft_strlcpy(*val, equal_pos + 1, len + 1);
	return (OK);
}

static void	error_invalid_id(char * id)
{
	write(STDERR, "minishell: export: `", 20);
	write(STDERR, id, ft_strlen(id));
	write(STDERR, "': not a valid identifier\n", 26);
}
