/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:29 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 19:16:35 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;
	char		*line;

	init_minishell(&minishell, envp);
	init_system_vars(&minishell);
	if (argc == 3 && ft_streq(argv[1], "-c"))
	{
		line = ft_strdup(argv[2]);
		shell(&minishell, &line);
	}
	else if (isatty(STDIN) == 0)
	{
		line = get_next_line(STDIN);
		while (line)
		{
			shell(&minishell, &line);
			line = get_next_line(STDIN);
		}
	}
	else
		shell_loop(&minishell);
	destroy_minishell(&minishell);
	return (minishell.exit_status);
}
