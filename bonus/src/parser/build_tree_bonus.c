/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:28:17 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 15:21:01 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static t_bool	is_operand(t_tree *t);
static int		build_tree_node(t_node **tmp_stack, t_tree *root);

t_tree	*build_tree_postfix(t_ms *ms)
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
	return (t->type == TREE_TYPE_CMD || t->type == TREE_TYPE_IGNORE);
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

t_tree	*new_cmd_node(void)
{
	t_tree	*cmd_node;

	cmd_node = malloc(sizeof(*cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = TREE_TYPE_CMD;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	cmd_node->content = new_command();
	return (cmd_node);
}

int	new_op_node(t_tree	**op_node, t_tree_type op_type)
{
	*op_node = malloc(sizeof(**op_node));
	if (!op_node)
		return (ERR_ALLOC);
	(*op_node)->type = op_type;
	(*op_node)->left = NULL;
	(*op_node)->right = NULL;
	(*op_node)->content = NULL;
	return (OK);
}
