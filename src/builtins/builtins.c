/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:58:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/13 13:24:15 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(char *prompt, t_vlst *vars)
{
	char	**list_args;
	int		len_args;
	int		i;

	len_args = ft_split_count(prompt, ' ');
	list_args = ft_split(prompt, ' ');
	if (len_args == 0)
		return ;
	if (command_is_equal(list_args[0], "echo"))
	{
		if (len_args == 3 && command_is_equal(list_args[1], "-n"))
			builtin_echo("-n", list_args[2]);
		else if (len_args == 2)
			builtin_echo("", list_args[1]);
	}
	else if (command_is_equal(list_args[0], "cd") && len_args == 2)
		builtin_cd(list_args[1], vars);
	else if (command_is_equal(prompt, "pwd"))
		builtin_pwd();
	else if (command_is_equal(list_args[0], "env"))
		builtin_env(vars);
	else if (command_is_equal(list_args[0], "export"))
		builtin_export(len_args, list_args, vars);
	else if (command_is_equal(list_args[0], "unset"))
		builtin_unset(len_args, list_args, vars);
	else
		printf("exec: %s\n", prompt);
	i = -1;
	while (++i < len_args)
		free(list_args[i]);
	free(list_args);
}
