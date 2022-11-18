/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:01:34 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/18 15:28:28 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic_error(char *msg)
{
	char	*err;

	err = "Panic Error: ";
	write(STDERR, err, ft_strlen(err));
	write(STDERR, msg, ft_strlen(msg));
	write(STDERR, "\n", 1);
}

int	error_message(int status, char *fields[])
{
	if (!fields)
		return (status);
	ft_putstr_fd("minishell", STDERR);
	while (*fields)
	{
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(*fields, STDERR);
		++fields;
	}
	ft_putstr_fd("\n", STDERR);
	return (status);
}
