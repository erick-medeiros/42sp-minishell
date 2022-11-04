/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:58:37 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/04 17:03:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int number)
{
	size_t	i;
	int		original;
	char	s[12];

	if (number == -2147483648)
		return (ft_strdup("-2147483648"));
	if (number == 0)
		return (ft_strdup("0"));
	original = number;
	if (number < 0)
		number = number * -1;
	s[11] = '\0';
	i = 11;
	while (number != 0)
	{
		i--;
		s[i] = (number % 10) + '0';
		number = number / 10;
	}
	if (original < 0)
	{
		i--;
		s[i] = '-';
	}
	return (ft_strdup(&s[i]));
}
