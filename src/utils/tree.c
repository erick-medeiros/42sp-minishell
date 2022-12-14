/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:07:57 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/07 12:54:43 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*new_tree_node(t_tree_type type)
{
	t_tree	*tree_node;

	tree_node = malloc(sizeof(t_tree));
	tree_node->type = type;
	tree_node->content = NULL;
	tree_node->left = NULL;
	tree_node->right = NULL;
	return (tree_node);
}

void	*destroy_tree(t_tree *root, void (*destroy_content)(void *))
{
	if (!root)
		return (NULL);
	if (root->left)
		root->left = destroy_tree(root->left, destroy_content);
	if (root->right)
		root->right = destroy_tree(root->right, destroy_content);
	if (destroy_content)
		destroy_content(root);
	free(root);
	return (NULL);
}

void	destroy_execution_tree(void *root)
{
	t_tree	*node;

	node = root;
	if (!node->content)
		return ;
	if (node->type == TREE_TYPE_CMD)
		destroy_command(node->content);
}

void	del_cmd_tree_node(void *tree)
{
	t_tree	*node;

	node = (t_tree *)tree;
	if (node->type == TREE_TYPE_CMD && node->content != NULL)
		destroy_command((t_cmd *)(node->content));
	free(node);
}
