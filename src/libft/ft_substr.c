/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:42:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/06 13:57:41 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	size;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (slen - start > len)
		size = len + 1;
	else
		size = slen - start + 1;
	sub = (char *) malloc(sizeof(char) * size);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, (s + start), size);
	return (sub);
}
