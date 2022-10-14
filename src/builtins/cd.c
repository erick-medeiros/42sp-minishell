/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:49 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/13 14:39:36 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//cd — change the working directory

void	builtin_cd(char *path, t_vlst *vars)
{
	char	*retptr;

	chdir(path);
	retptr = get_pwd();
	if (retptr)
	{
		update_var(vars, new_var_node_from_name_val("PWD", retptr));
		free(retptr);
	}
}
