/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:41:18 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/24 18:53:17 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	isbuiltin(char *arg)
{
	if (ft_strcmp(arg, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(arg, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(arg, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(arg, "export") == 0)
		return (TRUE);
	else if (ft_strcmp(arg, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(arg, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(arg, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

void	configure_builtin(t_cmd *command)
{
	if (!command->isbuiltin)
		return ;
	if (ft_strcmp(command->argv[0], "echo") == 0)
		command->subshell = TRUE;
	else if (ft_strcmp(command->argv[0], "cd") == 0)
		command->subshell = FALSE;
	else if (ft_strcmp(command->argv[0], "pwd") == 0)
		command->subshell = TRUE;
	else if (ft_strcmp(command->argv[0], "export") == 0)
		command->subshell = TRUE;
	else if (ft_strcmp(command->argv[0], "unset") == 0)
		command->subshell = TRUE;
	else if (ft_strcmp(command->argv[0], "env") == 0)
		command->subshell = TRUE;
	else if (ft_strcmp(command->argv[0], "exit") == 0)
		command->subshell = FALSE;
}
