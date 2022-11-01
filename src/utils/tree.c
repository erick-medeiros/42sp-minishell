/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:07:57 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/01 16:12:59 by eandre-f         ###   ########.fr       */
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

void	*destroy_tree(t_tree *root, void (*destroy)(t_tree *))
{
	if (!root)
		return (NULL);
	if (root->left)
		root->left = destroy_tree(root->left, destroy);
	if (root->right)
		root->right = destroy_tree(root->right, destroy);
	if (destroy)
		destroy(root);
	free(root);
	return (NULL);
}
