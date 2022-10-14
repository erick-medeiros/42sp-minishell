/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:52:31 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/14 01:11:35 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

static void	change_or_create_var(t_vlst *vars, char *str);
static void	print_sorted_vars(t_vlst *vars, char *prefix);
static size_t	partition(char** envp, size_t start_idx, size_t end_idx);
static void	quicksort(char** envp, size_t start_idx, size_t end_idx);

// TODO: sanitize args
void	builtin_export(int argc, char *argv[], t_vlst *vars)
{
	int		idx;

	if (argc == 1)
	{
		print_sorted_vars(vars, " declare - x ");
		return ;
	}
	idx = 1;
	while (idx < argc)
		change_or_create_var(vars, argv[idx++]);
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

static void	change_or_create_var(t_vlst *vars, char *str)
{
	t_var			*content;
	t_node_funcs	funcs;

	funcs.clear = del_var_node;
	funcs.cmp = cmp_vars_by_name;
	content = new_var_node_from_str(str);
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

static size_t	partition(char** envp, size_t start_idx, size_t end_idx)
{
	char	*pivot;
	char	*tmp;
	size_t	i;
	size_t	j;

	pivot = envp[end_idx];
	i = start_idx;
	j = start_idx;
	while (j < end_idx)
	{
		if (ft_strcmp(envp[j], pivot) <= 0)
		{
			tmp = envp[j];
			envp[j] = envp[i];
			envp[i] = tmp;
			i++;
		}
		j++;
	}
	tmp = envp[end_idx];
	envp[end_idx] = envp[i];
	envp[i] = tmp;
	return (i);
}

static void	quicksort(char** envp, size_t start_idx, size_t end_idx)
{
	size_t	pivot_idx;

	if (start_idx < end_idx)
	{
		pivot_idx = partition(envp, start_idx, end_idx);
		quicksort(envp, start_idx, pivot_idx - 1);
		quicksort(envp, pivot_idx + 1, end_idx);
	}
}
