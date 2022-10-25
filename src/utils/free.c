/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:38:19 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/25 09:42:04 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_internals.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}

void	free_minishell(t_minishell *minishell)
{
	clear_list(minishell->pipelines, (void (*)(void *))destroy_pipeline);
	clear_list(minishell->token_list, free_token);
}

void	destroy_minishell(t_minishell *minishell)
{
	free_minishell(minishell);
	clear_list(minishell->env_list.list, del_var_node);
	free_string_list(minishell->path_list);
}

void	free_string_list(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
