/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:28:17 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/12 23:54:10 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static t_bool	is_operand(t_tree *t);
static int		build_tree_node(t_node **tmp_stack, t_tree *root);

t_tree	*build_tree_postfix(t_minishell *ms)
{
	t_node	*tmp_stack;
	t_tree	*root;

	tmp_stack = NULL;
	if (ms->cmd_list.front == NULL
		|| ((t_tree *)ms->cmd_list.front->content)->type != TREE_TYPE_CMD)
		return (NULL);
	if (ms->cmd_list.front == ms->cmd_list.rear)
		return (dequeue(&ms->cmd_list));
	root = dequeue(&ms->cmd_list);
	while (root != NULL)
	{
		build_tree_node(&tmp_stack, root);
		root = dequeue(&ms->cmd_list);
	}
	return (pop_node(&tmp_stack));
}

static t_bool	is_operand(t_tree *t)
{
	return (t->type == TREE_TYPE_CMD || t->content);
}

static int	build_tree_node(t_node **tmp_stack, t_tree *root)
{
	int	result;

	if (is_operand(root))
		result = push_node(tmp_stack, root);
	else
	{
		root->right = pop_node(tmp_stack);
		root->left = pop_node(tmp_stack);
		root->content = (void *)1;
		result = push_node(tmp_stack, root);
		if (!root->left || !root->right)
			result = ERR_ALLOC;
	}
	if (result != OK)
	{
		destroy_tree(root, del_cmd_tree_node);
		clear_list(*tmp_stack, del_cmd_tree_node);
		return (result);
	}
	return (OK);
}
