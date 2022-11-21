/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:29 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/21 04:03:13 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;
	char		*line;
	int			status;

	init_minishell(&minishell, envp);
	init_system_vars(&minishell.env_list);
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
	status = minishell.env_list.last_status;
	destroy_minishell(&minishell);
	return (status);
}
