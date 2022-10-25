/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:29 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/25 10:05:45 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	(void)envp;
	minishell.path_list = get_paths(envp);
	envp_to_list(envp, &minishell.env_list);
	minishell.envp = envp;
	signal(SIGQUIT, SIG_IGN);
	miniprompt(&minishell);
	clear_list(minishell.env_list.list, del_var_node);
	return (0);
}
