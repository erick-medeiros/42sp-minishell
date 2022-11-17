/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:39:54 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/16 20:41:37 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

int	builtin_env(int fd_out, t_vlst *vars)
{
	char	**envp;
	char	**tmp;

	envp = list_to_envp(vars, NULL, 0);
	tmp = envp;
	while (*envp)
		ft_putendl_fd(*envp++, fd_out);
	clear_envp(tmp);
	return (OK);
}
