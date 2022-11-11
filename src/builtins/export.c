/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:52:31 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/11 03:26:18 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"
#include "minishell.h"

static void	change_or_create_var(t_vlst *vars, char *name, char *val);
static void		print_sorted_vars(t_vlst *vars, char *prefix);
static size_t	partition(char **envp, size_t start_idx, size_t end_idx);

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
	{

		if (!is_valid_name(content->name))
		{
			write(STDERR, "minishell: export: `", 20);
			write(STDERR, argv[idx], ft_strlen(argv[idx]));
			write(STDERR, "': not a valid identifier\n", 26);
			continue ;
		}
		change_or_create_var(vars, argv[idx++]);
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

	if (!str)
		return (ERR_NOT_FOUND);
	equal_pos = ft_strchr(str, '=');
	if (!equal_pos)
		return (ERR_NOT_FOUND);
	*name = malloc(sizeof(*content));
	if (!content)
		return (NULL);
}
