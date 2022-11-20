/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:52:55 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/19 16:16:07 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	is_negative;
	int	result;

	result = 0;
	is_negative = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		is_negative = 1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = 10 * result - (int)(*nptr - '0');
		nptr++;
	}
	if (is_negative)
		return (result);
	return (-result);
}
