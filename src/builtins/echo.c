/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:37 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/18 17:53:26 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(int fd_out, char *argv[])
{
	t_bool	option_n;
	int		i;
	int		j;

	option_n = TRUE;
	i = 1;
	while (argv && ft_strlen(argv[i]) > 1 && argv[i][0] == '-')
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j++] == 'n')
				option_n = FALSE;
		}
		++i;
	}
	while (argv && argv[i])
	{
		ft_putstr_fd(argv[i], fd_out);
		if (argv[++i])
			ft_putstr_fd(" ", fd_out);
	}
	if (option_n)
		ft_putstr_fd("\n", fd_out);
	return (OK);
}
