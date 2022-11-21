/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postfix_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 02:42:05 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/21 04:01:39 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "parser_bonus.h"

static int	transfer_node(t_node **src, t_queue *dst);

int	push_postfix(t_node **tmp_stack, t_queue *cmds, t_tree *tree)
{
	if (is_op(tree->type))
	{
		while (*tmp_stack != NULL)
		{
			if (transfer_node(tmp_stack, cmds))
				return (ERR_ALLOC);
		}
		return (push_node(tmp_stack, tree));
	}
	return (enqueue(cmds, tree));
}

int	flush_postfix(t_node **tmp_stack, t_queue *cmds)
{
	while (*tmp_stack != NULL)
	{
		if (transfer_node(tmp_stack, cmds))
			return (ERR_ALLOC);
	}
	return (OK);
}

static int	transfer_node(t_node **src, t_queue *dst)
{
	t_node	*popped;
	int		result;

	if (*src == NULL)
		return (OK);
	popped = *src;
	*src = (*src)->next;
	result = enqueue(dst, popped->content);
	free(popped);
	return (result);
}
