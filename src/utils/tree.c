/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 00:44:36 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/31 19:40:20 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

t_tree_node	*new_tree_node(t_op_type op_type, t_cmd *cmd,
				t_tree_node *left, t_tree_node *right)
{
	t_tree_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	new_node->cmd = cmd;
	new_node->op = op_type;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

void	del_tree_node(t_tree_node *node)
{
	destroy_command(node->cmd);
	free(node);
}

void	clear_tree(t_tree_node *root)
{
	if (root->left)
		clear_tree(root->left);
	if (root->right)
		clear_tree(root->right);
	del_tree_node(root);
}
