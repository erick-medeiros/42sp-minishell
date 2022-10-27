/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:01:34 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/22 14:25:20 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic_error(char *msg)
{
	write(STDERR, msg, ft_strlen(msg));
	write(STDERR, "\n", 1);
	exit(1);
}
