/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postfix.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 02:42:05 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/25 11:25:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	push_postfix_parenthesis(t_node **opstack, t_queue *cmds,
				t_tree *tree);
static int	transfer_node(t_node **src, t_queue *dst);

int	push_postfix(t_node **opstack, t_queue *cmds, t_tree *tree)
{
	if (tree->type == TREE_TYPE_OPAR || tree->type == TREE_TYPE_CPAR)
		return (push_postfix_parenthesis(opstack, cmds, tree));
	if (is_op(tree->type))
	{
		while (*opstack != NULL
			&& ((t_tree*)(*opstack)->content)->type != TREE_TYPE_OPAR
			&& ((t_tree*)(*opstack)->content)->type != TREE_TYPE_CPAR)
		{
			if (transfer_node(opstack, cmds))
				return (ERR_ALLOC);
		}
		return (push_node(opstack, tree));
	}
	return (enqueue(cmds, tree));
}

static int	push_postfix_parenthesis(t_node **opstack, t_queue *cmds,
				t_tree *tree)
{
	if (tree->type == TREE_TYPE_OPAR)
		return (push_node(opstack, tree));
	if (tree->type == TREE_TYPE_CPAR)
	{
		del_cmd_tree_node(tree);
		while (*opstack != NULL
			&& ((t_tree*)(*opstack)->content)->type != TREE_TYPE_OPAR)
		{
			if (transfer_node(opstack, cmds))
				return (ERR_ALLOC);
		}
		if (*opstack != NULL
			&& ((t_tree*)(*opstack)->content)->type == TREE_TYPE_OPAR)
			*opstack = remove_node(*opstack, del_cmd_tree_node);
		return (OK);
	}
	return (1);
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
