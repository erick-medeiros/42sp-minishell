/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:38:59 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 08:56:22 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// string is equal

int	ft_streq(char *str1, char *str2)
{
	int	len;

	len = ft_max(ft_strlen(str1), ft_strlen(str2));
	if (ft_strncmp(str1, str2, len) == 0)
		return (TRUE);
	return (FALSE);
}
