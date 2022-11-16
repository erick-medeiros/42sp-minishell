/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:49 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/16 13:04:20 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "expander.h"
#include "structs.h"

//cd — change the working directory

int	builtin_cd(char *path, t_vlst *vars)
{
	char	*retptr;
	t_node	*node;

	chdir(path);
	retptr = get_pwd();
	if (retptr)
	{
		if (vars)
		{
			node = find_node_by_content(vars->list, "PWD", find_env_var);
			if (node)
				update_var(vars, new_var_node_from_name_val("OLDPWD",
						((t_var *)node->content)->val));
			update_var(vars, new_var_node_from_name_val("PWD", retptr));
		}
		free(retptr);
	}
	return (OK);
}
