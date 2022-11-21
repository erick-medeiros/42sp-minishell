/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:39:54 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/21 03:53:35 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "expander_bonus.h"

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
