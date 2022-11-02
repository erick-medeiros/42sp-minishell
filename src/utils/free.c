/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:38:19 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/01 19:46:43 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	destroy_execution_tree(t_tree *root)
{
	if (root->type == TREE_TYPE_CMD)
		destroy_command(root->content);
}
