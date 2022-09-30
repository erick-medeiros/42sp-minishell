/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:06:25 by eandre-f          #+#    #+#             */
/*   Updated: 2022/09/29 17:11:25 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_max(int number1, int number2)
{
	if (number1 > number2)
		return (number1);
	else
		return (number2);
}

int	ft_min(int number1, int number2)
{
	if (number1 < number2)
		return (number1);
	else
		return (number2);
}
