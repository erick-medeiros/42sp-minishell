/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 03:37:27 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/12 17:13:04 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	push_node(t_node **lst, void *content)
{
	t_node	*new_node;

	if (!lst)
		return (ERR_NOT_FOUND);
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (ERR_ALLOC);
	new_node->content = content;
	new_node->next = *lst;
	*lst = new_node;
	return (OK);
}

void	*pop_node(t_node **src)
{
	t_node	*popped;
	void	*content;

	if (*src == NULL)
		return (NULL);
	popped = *src;
	*src = popped->next;
	content = popped->content;
	free(popped);
	return (content);
}
