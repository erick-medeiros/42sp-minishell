/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:19:38 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/25 17:28:09 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->path_list = get_paths(envp);
	envp_to_list(envp, &minishell->env_list);
	minishell->envp = envp;
}
