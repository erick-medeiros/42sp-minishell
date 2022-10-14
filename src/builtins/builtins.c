/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:58:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/14 01:59:34 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	call_builtin(char *prompt, int argc, char **argv, t_vlst *vars);

void	builtins(char *prompt, t_vlst *vars)
{
	char	**list_args;
	int		len_args;
	int		i;

	len_args = ft_split_count(prompt, ' ');
	list_args = ft_split(prompt, ' ');
	if (len_args == 0)
		return ;
	call_builtin(prompt, len_args, list_args, vars);
	i = -1;
	while (++i < len_args)
		free(list_args[i]);
	free(list_args);
}

static void	call_builtin(char *prompt, int argc, char **argv, t_vlst *vars)
{
	if (command_is_equal(argv[0], "echo"))
	{
		if (argc == 3 && command_is_equal(argv[1], "-n"))
			builtin_echo("-n", argv[2]);
		else if (argc == 2)
			builtin_echo("", argv[1]);
	}
	else if (command_is_equal(argv[0], "cd") && argc == 2)
		builtin_cd(argv[1], vars);
	else if (command_is_equal(prompt, "pwd"))
		builtin_pwd();
	else if (command_is_equal(argv[0], "env"))
		builtin_env(vars);
	else if (command_is_equal(argv[0], "export"))
		builtin_export(argc, argv, vars);
	else if (command_is_equal(argv[0], "unset"))
		builtin_unset(argc, argv, vars);
	else
		printf("exec: %s\n", prompt);
}
