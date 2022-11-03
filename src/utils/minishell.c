/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:19:38 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/03 03:13:15 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansor.h"
#include "parser.h"

void	free_token(void *content);

void	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->root = NULL;
	minishell->token_list = NULL;
	minishell->heredoc_queue.front = NULL;
	minishell->heredoc_queue.rear = NULL;
	minishell->env_list.len = 0;
	minishell->env_list.list = NULL;
	minishell->cmd_list = NULL;
	minishell->last_result = 0;
	if (envp)
		envp_to_list(envp, &minishell->env_list);
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->heredoc_queue.front)
	{
		clear_list(minishell->heredoc_queue.front, del_heredoc_node);
		minishell->heredoc_queue.front = NULL;
		minishell->heredoc_queue.rear = NULL;
	}
	if (minishell->token_list)
	{
		clear_list(minishell->token_list, free_token);
		minishell->token_list = NULL;
	}
	if (minishell->cmd_list)
	{
		clear_list(minishell->cmd_list, free_token);
		minishell->cmd_list = NULL;
	}
	if (minishell->root)
	{
		destroy_tree(minishell->root, destroy_execution_tree);
		minishell->root = NULL;
	}
}

void	destroy_minishell(t_minishell *minishell)
{
	free_minishell(minishell);
	if (minishell->env_list.list)
		clear_list(minishell->env_list.list, del_var_node);
	if (minishell->heredoc_queue.front)
		clear_list(minishell->heredoc_queue.front, del_heredoc_node);
	if (minishell->cmd_list)
		clear_list(minishell->cmd_list, free_token);
	rl_clear_history();
}
