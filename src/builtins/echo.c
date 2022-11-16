/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:37 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/16 13:05:38 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "structs.h"

void	builtin_echo_output(t_cmd *cmd, int i, t_bool	option_n)
{
	while (cmd->argv[i])
	{
		write(STDOUT, cmd->argv[i], ft_strlen(cmd->argv[i]));
		++i;
		if (cmd->argv[i])
			write(STDOUT, " ", 1);
	}
	if (option_n)
		write(STDOUT, "\n", 1);
}

int	builtin_echo(t_cmd *cmd)
{
	t_bool	option_n;
	int		i;
	int		j;

	if (cmd->argc == 1)
		return (OK);
	option_n = TRUE;
	i = 1;
	while (ft_strlen(cmd->argv[i]) > 1 && cmd->argv[i][0] == '-')
	{
		j = 1;
		while (cmd->argv[i][j])
		{
			if (cmd->argv[i][j] == 'n')
				option_n = FALSE;
			else
				panic_error("builtin echo");
			++j;
		}
		++i;
	}
	builtin_echo_output(cmd, i, option_n);
	return (OK);
}
