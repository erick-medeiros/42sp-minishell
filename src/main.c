/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:29 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/10 00:46:57 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;
	char		*line;

	init_minishell(&minishell, envp);
	if (argc == 3 && command_is_equal(argv[1], "-c"))
	{
		line = ft_strdup(argv[2]);
		shell(&minishell, &line);
	}
	else
		shell_loop(&minishell);
	destroy_minishell(&minishell);
	return (minishell.exit_status);
}
