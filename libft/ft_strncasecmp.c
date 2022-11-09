/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncasecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:04:28 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/09 19:13:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

int	ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1uc;
	unsigned char	*s2uc;
	unsigned char	c1;
	unsigned char	c2;

	s1uc = (unsigned char *) s1;
	s2uc = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		c1 = ft_tolower(s1uc[i]);
		c2 = ft_tolower(s2uc[i]);
		if (c1 != c2 || c1 == '\0' || c2 == '\0')
			return (c1 - c2);
		i++;
	}
	return (0);
}
