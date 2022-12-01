/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:37 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/01 19:21:58 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	get_option_n(char *arg);
static int		write_error(int error);

int	builtin_echo(int fd_out, char *argv[])
{
	t_bool	option_n;
	int		i;

	option_n = TRUE;
	i = 1;
	while (argv && ft_strlen(argv[i]) > 1 && argv[i][0] == '-')
		option_n = get_option_n(argv[i++]);
	while (argv && argv[i])
	{
		if (write(fd_out, argv[i], ft_strlen(argv[i])) == -1)
			return (write_error(errno));
		if (argv[++i])
			if (write(fd_out, " ", 1) == -1)
				return (write_error(errno));
	}
	if (option_n)
		if (write(fd_out, "\n", 1) == -1)
			return (write_error(errno));
	return (OK);
}

static	t_bool	get_option_n(char *arg)
{
	t_bool	option_n;
	int		j;

	j = 1;
	while (arg[j])
	{
		if (arg[j++] == 'n')
			option_n = FALSE;
	}
	return (option_n);
}

static int	write_error(int error)
{
	return (error_message3(1, "echo", "write error", strerror(error)));
}
