/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:38:19 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/10 03:45:47 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
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

void	destroy_execution_tree(void *root)
{
	if (((t_tree *)root)->type == TREE_TYPE_CMD)
		destroy_command(((t_tree *)root)->content);
}

void	destroy_redirect(t_redirect *redirect)
{
	if (!redirect)
		return ;
	free(redirect->path);
	free(redirect);
}
