/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:52:31 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/12 13:52:28 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_sorted_vars(t_vlst *vars, char *prefix);

// TODO: sort variables before printing
void	builtin_export(int argc, char *argv[], t_vlst *vars)
{
	t_var	*content;

	if (argc == 1)
	{
		print_sorted_vars(vars, " declare - x ");
		return ;
	}
	while (--argc > 0)
	{
		content = new_var_node(argv[argc]);
		if (!content)
			continue ;
		if (change_node_content(vars->list, content,
				content, cmp_vars_by_name))
		{
			if (add_node(&(vars->list), content))
			{
				del_var_node(content);
				return ;
			}
			vars->len++;
		}
	}
}

void	print_sorted_vars(t_vlst *vars, char *prefix)
{
	char	**envp;

	envp = list_to_envp(vars);
	while (envp)
		printf("%s%s\n", prefix, *envp++);
	clear_envp(envp);
}
