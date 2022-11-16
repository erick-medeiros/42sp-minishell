/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:10:27 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/16 13:07:40 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "builtins.h"

int	builtin_unset(int argc, char *argv[], t_vlst *vars)
{
	t_var	*content;
	int		removed;
	int		idx;

	if (argc < 2)
		return (OK);
	idx = 0;
	while (idx++ < argc)
	{
		if (!is_valid_name(argv[idx]))
			continue ;
		content = new_var_node_from_name_val(argv[idx], "");
		removed = remove_node_by_content(&(vars->list), content,
				del_var_node, cmp_vars_by_name);
		if (removed == OK)
			vars->len--;
		del_var_node(content);
	}
	return (OK);
}
