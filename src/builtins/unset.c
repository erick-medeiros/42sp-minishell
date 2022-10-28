/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:10:27 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/28 19:48:39 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansor.h"

void	builtin_unset(int argc, char *argv[], t_vlst *vars)
{
	t_var	*content;
	int		removed;

	if (argc < 2)
		return ;
	while (--argc > 0)
	{
		content = new_var_node_from_name_val(argv[argc], "");
		removed = remove_node_by_content(&(vars->list), content,
				del_var_node, cmp_vars_by_name);
		if (removed == OK)
			vars->len--;
		del_var_node(content);
	}
}
