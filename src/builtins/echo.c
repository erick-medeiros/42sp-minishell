/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:37 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/06 13:38:17 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char *option, char *string)
{
	write(STDOUT, string, ft_strlen(string));
	if (command_is_equal(option, "-n") == FALSE)
		write(STDOUT, "\n", 1);
}
