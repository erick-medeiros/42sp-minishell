/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:49 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/28 19:47:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "expansor.h"

//cd — change the working directory

void	builtin_cd(char *path, t_vlst *vars)
{
	char	*retptr;

	chdir(path);
	retptr = get_pwd();
	if (retptr)
	{
		if (vars)
			update_var(vars, new_var_node_from_name_val("PWD", retptr));
		free(retptr);
	}
}
