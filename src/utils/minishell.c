/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:19:38 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/02 15:08:08 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "parser.h"

void	free_token(void *content);

void	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->token_list = NULL;
	minishell->env_list.len = 0;
	minishell->env_list.list = NULL;
	minishell->cmd_list.front = NULL;
	minishell->cmd_list.rear = NULL;
	minishell->set_history = TRUE;
	minishell->env_list.last_status = 0;
	if (envp)
		envp_to_list(envp, &minishell->env_list);
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->token_list)
	{
		clear_list(minishell->token_list, free_token);
		minishell->token_list = NULL;
	}
	if (minishell->cmd_list.front)
	{
		clear_list(minishell->cmd_list.front, del_cmd_tree_node);
		minishell->cmd_list.front = NULL;
		minishell->cmd_list.rear = NULL;
	}
}

void	destroy_minishell(t_minishell *minishell)
{
	free_minishell(minishell);
	if (minishell->env_list.list)
		clear_list(minishell->env_list.list, del_var_node);
	rl_clear_history();
}
