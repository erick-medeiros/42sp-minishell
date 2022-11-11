/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:10:27 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/11 03:02:24 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "builtins.h"
#include "libft.h"

void	builtin_unset(int argc, char *argv[], t_vlst *vars)
{
	t_var	*content;
	int		removed;
	int		idx;

	if (argc < 2)
		return ;
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
