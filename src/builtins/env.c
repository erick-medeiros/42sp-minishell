/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:39:54 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/06 02:26:32 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

void	builtin_env(t_vlst *vars)
{
	char	**envp;
	char	**tmp;

	envp = list_to_envp(vars, 0);
	tmp = envp;
	while (*envp)
		printf("%s\n", *envp++);
	clear_envp(tmp);
}
