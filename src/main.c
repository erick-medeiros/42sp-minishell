/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:10:29 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/13 13:56:08 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_vlst	env_list;

	(void)argc;
	(void)argv;
	(void)envp;
	envp_to_list(envp, &env_list);
	signal(SIGQUIT, SIG_IGN);
	miniprompt(&env_list);
	clear_list(env_list.list, del_var_node);
	return (0);
}
