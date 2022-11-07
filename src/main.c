/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:29 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/07 20:30:14 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;

	init_minishell(&minishell, envp);
	if (argc == 3 && command_is_equal(argv[1], "-c"))
		shell(&minishell, ft_strdup(argv[2]));
	else
		shell_loop(&minishell);
	destroy_minishell(&minishell);
	return (minishell.exit_status);
}
