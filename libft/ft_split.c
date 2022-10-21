/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:41:46 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/21 17:17:19 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_split_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}	
		else
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	**splited;

	if (s == NULL)
		return (NULL);
	splited = malloc(sizeof(char *) * (ft_split_count(s, c) + 1));
	if (splited == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			splited[i++] = ft_substr(s, 0, len);
			s += len;
		}
		else
			s++;
	}
	splited[i] = NULL;
	return (splited);
}
