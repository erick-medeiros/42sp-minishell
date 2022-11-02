/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:37 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 12:01:01 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_cmd *command)
{
	if (command->argc == 3 && command_is_equal(command->argv[1], "-n"))
		write(STDOUT, command->argv[2], ft_strlen(command->argv[2]));
	else if (command->argc == 2)
	{
		write(STDOUT, command->argv[1], ft_strlen(command->argv[1]));
		write(STDOUT, "\n", 1);
	}
}
