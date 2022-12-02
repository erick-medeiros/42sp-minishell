/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:29 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/02 12:32:25 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_ms	ms;
	char	*line;
	int		status;

	init_minishell(&ms, envp);
	init_system_vars(&ms.env_list);
	if (argc == 3 && ft_streq(argv[1], "-c"))
	{
		line = ft_strdup(argv[2]);
		shell(&ms, &line);
	}
	else if (isatty(STDIN) == 0)
	{
		line = get_next_line(STDIN);
		while (line)
		{
			shell(&ms, &line);
			line = get_next_line(STDIN);
		}
	}
	else
		shell_loop(&ms);
	status = ms.env_list.last_status;
	destroy_minishell(&ms);
	return (status);
}
