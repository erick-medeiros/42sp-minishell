/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:32:03 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/02 11:12:13 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_ptr_content(void *content)
{
	free(content);
}

void clear_list(t_node *lst, void (*del_node)(void *))
{
	t_node	*tmp;

	while (lst)
	{
		del_node(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}
