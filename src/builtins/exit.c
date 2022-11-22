/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:54:16 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/22 13:42:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "minishell.h"

static int	get_command_status(int status, t_cmd *cmd)
{
	long long int	code;
	int				invalid;

	invalid = 0;
	if (cmd->argc > 1)
		code = ft_checked_atoll(cmd->argv[1], &invalid);
	if (invalid)
		return (error_message(ERR_BUILTIN, (char *[]){
				"exit", cmd->argv[1], "numeric argument required", NULL
			}));
	else if (cmd->argc > 2)
		return (error_message(1, (char *[]){
				"exit", "too many arguments", NULL
			}));
	else if (cmd->argc == 2)
		return (code % 256LL);
	return (status);
}

void	builtin_exit(int status, t_cmd *cmd)
{
	if (cmd)
		status = get_command_status(status, cmd);
	exit(status);
}
