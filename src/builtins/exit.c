/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:54:16 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/16 16:00:42 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "minishell.h"

static t_bool	is_numeric_argument(char *arg)
{
	char	*str;
	int		num;
	t_bool	cmp;

	if (!arg)
		return (FALSE);
	num = ft_atoi(arg);
	if (*arg == '+')
		++arg;
	while (*arg == '0' && ft_isdigit(arg[1]))
		++arg;
	str = ft_itoa(num);
	cmp = ft_streq(str, arg);
	free(str);
	return (cmp);
}

static int	get_command_status(int status, t_cmd *cmd)
{
	if (cmd->argc > 1 && !is_numeric_argument(cmd->argv[1]))
		return (error_message(ERR_BUILTIN, (char *[]){
				"exit", cmd->argv[1], "numeric argument required", NULL
			}));
	else if (cmd->argc > 2)
		return (error_message(1, (char *[]){
				"exit", "too many arguments", NULL
			}));
	else if (cmd->argc == 2)
		return (ft_atoi(cmd->argv[1]));
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
