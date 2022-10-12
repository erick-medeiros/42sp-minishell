/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:31:47 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/03 21:23:14 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_node(t_node **lst, void *content)
{
	t_node	*new_node;
	t_node	*current;

	if (!lst)
		return (ERR_NOT_FOUND);
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (ERR_ALLOC);
	new_node->content = content;
	new_node->next = NULL;
	if (!(*lst))
	{
		*lst = new_node;
		return (OK);
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (OK);
}

t_node	*find_node_by_content(t_node *lst, void *content,
	int (*cmp_content)(void *, void *))
{
	if (!lst || !cmp_content)
		return (NULL);
	while (lst)
	{
		if (cmp_content(content, lst->content) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	change_node_content(t_node *lst, void *old_content,
	void *new_content, int (*cmp_content)(void *, void *))
{
	t_node	*found;

	if (!lst || !cmp_content)
		return (ERR_NOT_FOUND);
	found = find_node_by_content(lst, old_content, cmp_content);
	if (!found)
		return (ERR_NOT_FOUND);
	free(found->content);
	found->content = new_content;
	return (OK);
}

t_node	*remove_node(t_node *current, void (*del_node)(void *))
{
	t_node	*tmp;

	tmp = current->next;
	del_node(current->content);
	free(current);
	return (tmp);
}

int	remove_node_by_content(t_node **lst, void *content,
	void (*del_node)(void *), int (*cmp_content)(void *, void *))
{
	t_node	*prev;

	if (!lst || !(*lst) || !del_node || !cmp_content)
		return (ERR_NOT_FOUND);
	if (cmp_content(content, (*lst)->content) == 0)
	{
		*lst = remove_node(*lst, del_node);
		return (OK);
	}
	prev = *lst;
	while (prev->next)
	{
		if (cmp_content(content, prev->next->content) == 0)
		{
			prev->next = remove_node(prev->next, del_node);
			return (OK);
		}
		prev = prev->next;
	}
	return (ERR_NOT_FOUND);
}