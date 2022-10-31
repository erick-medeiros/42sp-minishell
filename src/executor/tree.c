/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:20:55 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/31 14:06:21 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

#include "debug.h"

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

void	*destroy_tree(t_tree *root)
{
	if (root->left)
		root->left = destroy_tree(root->left);
	if (root->right)
		root->right = destroy_tree(root->right);
	if (root->type == TREE_TYPE_CMD)
	{
		destroy_command(root->content);
	}
	free(root);
	return (NULL);
}

t_tree	*insert_into_tree(t_tree *root, t_tree_type type, void *content)
{
	t_tree	*temp;
	t_tree	*current;
	t_tree	*parent;

	(void) parent;
	temp = new_tree_node(type);
	temp->content = content;
	if (root == NULL)
		root = temp;
	else
	{
		current = root;
		parent = NULL;
		if (current->type == TREE_TYPE_PIPE && current->right == NULL)
		{
			current->right = temp;
		}
		else
		{
			root = temp;
			root->left = current;
		}
	}
	return (root);
}

t_tree	*convert_list_to_tree(t_pipeline *pipeline)
{
	t_tree	*root;
	t_node	*list;

	root = NULL;
	list = pipeline->commands;
	while (list)
	{
		root = insert_into_tree(root, TREE_TYPE_CMD, list->content);
		list->content = NULL;
		list = list->next;
		if (list)
			root = insert_into_tree(root, TREE_TYPE_PIPE, NULL);
	}
	return (root);
}

void	tree_executor_recursive(t_minishell *minishell, t_tree *parent, t_tree *tree_node)
{
	if (tree_node->left)
		tree_executor_recursive(minishell, tree_node, tree_node->left);
	if (tree_node->right)
		tree_executor_recursive(minishell, tree_node, tree_node->right);
	if (tree_node->type == TREE_TYPE_CMD)
		printf(" cmd%d ", ((t_cmd *)tree_node->content)->number);
	if (tree_node->type == TREE_TYPE_PIPE)
		printf(" | ");
	(void) parent;
}

void	tree_executor(t_minishell *minishell, t_pipeline *pipeline)
{
	t_tree	*root;

	root = convert_list_to_tree(pipeline);
	tree_executor_recursive(minishell, NULL, root);
	printf("\n");
	destroy_tree(root);
}
