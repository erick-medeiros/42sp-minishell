/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:38:59 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/18 15:35:25 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// string is equal

int	ft_streq(char *str1, char *str2)
{
	int	len;

	len = ft_max(ft_strlen(str1), ft_strlen(str2));
	if (ft_strncmp(str1, str2, len) == 0)
		return (TRUE);
	return (FALSE);
}

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
