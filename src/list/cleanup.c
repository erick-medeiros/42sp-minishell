/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:32:03 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/03 21:06:55 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_ptr_content(void *content)
{
	free(content);
}

void	clear_list(t_node *lst, void (*del_node)(void *))
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
