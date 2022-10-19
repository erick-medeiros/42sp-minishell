/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:03:12 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/19 19:17:46 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*us;
	unsigned char	uc;
	int				i;

	us = (unsigned char *) s;
	uc = (unsigned char) c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (us[i] == uc)
			return ((char *) &us[i]);
		i--;
	}
	if (uc == '\0')
		return ((char *) &us[i]);
	return (NULL);
}
