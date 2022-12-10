/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:10:27 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/10 16:15:40 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "builtins.h"

static int	unset_error_msg(int status, char *id);

int	builtin_unset(int argc, char *argv[], t_vlst *vars)
{
	t_var	*content;
	int		removed;
	int		idx;
	int		result;

	if (argc < 2)
		return (OK);
	result = 0;
	idx = 0;
	while (++idx < argc)
	{
		if (!is_valid_name(argv[idx]))
		{
			if (SHOW_UNSET_MSG)
				result = unset_error_msg(1, argv[idx]);
			continue ;
		}
		content = new_var_node_from_name_val(argv[idx], "");
		removed = remove_node_by_content(&(vars->list), content,
				del_var_node, cmp_vars_by_name);
		if (removed == OK)
			vars->len--;
		del_var_node(content);
	}
	return (result);
}

static int	unset_error_msg(int status, char *id)
{
	ft_putstr_fd("minishell: unset: `", STDERR);
	ft_putstr_fd(id, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
	return (status);
}
