/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 21:13:35 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/04 21:35:37 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "structs.h"

static void	transfer_node(t_node **src, t_node **dst);

int	push_infix(t_node **tmp_stack, t_node **cmds, t_tree *tree)
{
	if (is_op(tree->type))
	{
		while (tmp_stack != NULL)
			transfer_node(tmp_stack, cmds);
		return (add_node(tmp_stack, tree));
	}
	return (add_node(cmds, tree));
}

void	flush_infix(t_node **tmp_stack, t_node **cmds)
{
	while (tmp_stack != NULL)
		transfer_node(tmp_stack, cmds);
}

static void	transfer_node(t_node **src, t_node **dst)
{
	t_node	*popped;

	if (*src == NULL)
		return ;
	popped = *src;
	*src = (*src)->next;
	popped->next = *dst;
	*dst = popped;
}
