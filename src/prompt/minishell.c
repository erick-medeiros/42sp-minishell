/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:19:38 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/02 17:12:05 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "parser.h"

void	init_minishell(t_ms *ms, char **envp)
{
	ms->token_list = NULL;
	ms->env_list.len = 0;
	ms->env_list.list = NULL;
	ms->cmd_list.front = NULL;
	ms->cmd_list.rear = NULL;
	ms->set_history = TRUE;
	ms->env_list.last_status = 0;
	if (envp)
		envp_to_list(envp, &ms->env_list);
}

void	free_minishell(t_ms *ms)
{
	if (ms->token_list)
	{
		clear_list(ms->token_list, free_token);
		ms->token_list = NULL;
	}
	if (ms->cmd_list.front)
	{
		clear_list(ms->cmd_list.front, del_cmd_tree_node);
		ms->cmd_list.front = NULL;
		ms->cmd_list.rear = NULL;
	}
}

void	destroy_minishell(t_ms *ms)
{
	free_minishell(ms);
	if (ms->env_list.list)
		clear_list(ms->env_list.list, del_var_node);
	rl_clear_history();
}
