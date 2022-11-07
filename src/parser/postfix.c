/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postfix.c                                            :+:      :+:    :+:   */
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

static void	transfer_node(t_node **src, t_queue *dst);

int	push_postfix(t_node **tmp_stack, t_queue *cmds, t_tree *tree)
{
	if (is_op(tree->type))
	{
		while (*tmp_stack != NULL)
			transfer_node(tmp_stack, cmds);
		return (add_node(tmp_stack, tree));
	}
	return (enqueue(cmds, tree));
}

void	flush_postfix(t_node **tmp_stack, t_queue *cmds)
{
	while (*tmp_stack != NULL)
		transfer_node(tmp_stack, cmds);
}

static void	transfer_node(t_node **src, t_queue *dst)
{
	t_node	*popped;

	if (*src == NULL)
		return ;
	popped = *src;
	*src = (*src)->next;
	enqueue(dst, popped->content);
	free(popped);
}
