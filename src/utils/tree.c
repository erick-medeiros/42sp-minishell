/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:07:57 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/22 14:31:20 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

t_etree	*new_etree(void)
{
	t_etree	*etree;

	etree = malloc(sizeof(t_etree));
	etree->operator = OP_NONE;
	etree->cmd = NULL;
	etree->pid = 0;
	etree->status = 0;
	etree->input = STDIN;
	etree->output = STDOUT;
	etree->next = NULL;
	etree->group = NULL;
	etree->ispipeline = FALSE;
	return (etree);
}

void	*destroy_etree(t_etree *node)
{
	if (!node)
		return (NULL);
	if (node->group)
		node->group = destroy_etree(node->group);
	if (node->next)
		node->next = destroy_etree(node->next);
	if (node->cmd)
		destroy_command(node->cmd);
	free(node);
	return (NULL);
}

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

void	del_cmd_tree_node(void *tree)
{
	t_tree	*node;

	node = (t_tree *)tree;
	if (node->type == TREE_TYPE_CMD && node->content != NULL)
		destroy_command((t_cmd *)(node->content));
	free(node);
}
