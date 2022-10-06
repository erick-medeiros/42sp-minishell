/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:58:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/06 14:07:13 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(char *prompt)
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
		builtin_cd(list_args[1]);
	else if (command_is_equal(prompt, "pwd"))
		builtin_pwd();
	else
		printf("exec: %s\n", prompt);
	i = -1;
	while (++i < len_args)
		free(list_args[i]);
	free(list_args);
}
