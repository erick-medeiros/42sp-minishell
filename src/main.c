/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:29 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/25 17:26:06 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	init_minishell(&minishell, envp);
	signal(SIGQUIT, SIG_IGN);
	miniprompt(&minishell);
	destroy_minishell(&minishell);
	return (0);
}
