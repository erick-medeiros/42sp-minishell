/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checked_atoll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:59:08 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/17 04:25:10 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long int	get_next_positive_digit(long long int result,
							char ch, int *invalid);
static long long int	get_next_negative_digit(long long int result,
							char ch, int *invalid);

long long int	ft_checked_atoll(const char *nptr, int *invalid)
{
	long long int	result;

	result = 0;
	*invalid = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		nptr++;
		while (*nptr >= '0' && *nptr <= '9' && *invalid == 0)
			result = (get_next_negative_digit(result, *nptr++, invalid));
		if (*nptr != '\0')
			*invalid = 1;
		return (result);
	}
	if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9' && *invalid == 0)
		result = (get_next_positive_digit(result, *nptr++, invalid));
	if (*nptr != '\0')
			*invalid = 1;
	return (result);
}

static long long int	get_next_positive_digit(long long int result,
							char ch, int *invalid)
{
	long long int	new_result;

	new_result = 10 * result + (long long int)(ch - '0');
	if (new_result < result)
		*invalid = 1;
	return (new_result);
}

static long long int	get_next_negative_digit(long long int result,
							char ch, int *invalid)
{
	long long int	new_result;

	new_result = 10 * result - (long long int)(ch - '0');
	if (new_result > result)
		*invalid = 1;
	return (new_result);
}
