/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:31:21 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/17 16:32:10 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t len)
{
	size_t	len_s;
	char	*copy;

	len_s = len + 1;
	copy = malloc(len_s * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s, len_s);
	return (copy);
}
