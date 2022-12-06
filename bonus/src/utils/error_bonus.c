/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:47:42 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 15:22:16 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

int	error_message1(int status, char *field1)
{
	return (error_message(status, (char *[]){field1, 0}));
}

int	error_message2(int status, char *field1, char *field2)
{
	return (error_message(status, (char *[]){field1, field2, 0}));
}

int	error_message3(int status, char *field1, char *field2, char *field3)
{
	return (error_message(status, (char *[]){field1, field2, field3, 0}));
}
