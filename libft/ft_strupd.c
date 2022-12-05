/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:36:39 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/05 12:42:40 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// string allocation update

void	ft_strupd(char **str, char *newstr)
{
	char	*tmp;

	tmp = *str;
	*str = newstr;
	free(tmp);
}
