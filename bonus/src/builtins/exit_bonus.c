/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:54:16 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/21 03:52:56 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus.h"
#include "libft.h"
#include "minishell_bonus.h"

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

void	builtin_exit(int status, t_minishell *ms, t_cmd *cmd)
{
	if (cmd)
		status = get_command_status(status, cmd);
	if (ms)
		destroy_minishell(ms);
	exit(status);
}
