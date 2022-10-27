/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:19:38 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/27 18:34:52 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_internals.h"

void	free_token(void *content);

void	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->token_list = NULL;
	minishell->pipelines = NULL;
	minishell->path_list = NULL;
	minishell->env_list.len = 0;
	minishell->env_list.list = NULL;
	if (envp)
	{
		minishell->path_list = get_paths(envp);
		envp_to_list(envp, &minishell->env_list);
	}
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->pipelines)
	{
		clear_list(minishell->pipelines, (void (*)(void *))destroy_pipeline);
		minishell->pipelines = NULL;
	}
	if (minishell->token_list)
	{
		clear_list(minishell->token_list, free_token);
		minishell->token_list = NULL;
	}
}

void	destroy_minishell(t_minishell *minishell)
{
	free_minishell(minishell);
	if (minishell->env_list.list)
		clear_list(minishell->env_list.list, del_var_node);
	free_string_list(minishell->path_list);
	rl_clear_history();
}
