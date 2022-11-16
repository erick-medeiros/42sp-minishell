/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:39:54 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/16 13:06:08 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

int	builtin_env(t_vlst *vars)
{
	char	**envp;
	char	**tmp;

	envp = list_to_envp(vars, NULL, 0);
	tmp = envp;
	while (*envp)
		printf("%s\n", *envp++);
	clear_envp(tmp);
	return (OK);
}
