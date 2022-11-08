/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 01:22:27 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/08 19:54:22 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strappend(char **s1, char const *s2)
{
	char	*tmp;

	if (s2 == NULL)
		return ;
	if (*s1 == NULL)
	{
		*s1 = ft_strdup(s2);
		return ;
	}
	tmp = *s1;
	*s1 = ft_strjoin(*s1, s2);
	free(tmp);
}
