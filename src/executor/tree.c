/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:20:55 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 09:44:36 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	tree_executor_recursive(t_minishell *minishell, t_tree *grandparent,
			t_tree *parent, t_tree *root)
{
	t_cmd	*cmd;

	if (!root)
		return ;
	if (root->type == TREE_TYPE_PIPE)
	{
		root->content = malloc(sizeof(int) * 2);
		if (pipe(root->content) == -1)
			panic_error("tree executor ~ pipe");
	}
	if (root->left)
		tree_executor_recursive(minishell, parent, root, root->left);
	if (root->right)
		tree_executor_recursive(minishell, parent, root, root->right);
	if (root->type == TREE_TYPE_CMD)
	{
		cmd = (t_cmd *) root->content;
		connect_pipeline(cmd, grandparent, parent, root);
		subshell(minishell, cmd);
	}
}

void	wait_tree(t_tree *root)
{
	t_cmd	*cmd;

	if (!root)
		return ;
	if (root->left)
		wait_tree(root->left);
	if (root->right)
		wait_tree(root->right);
	if (root->type == TREE_TYPE_CMD)
	{
		cmd = (t_cmd *) root->content;
		if (cmd->subshell)
			waitpid(cmd->pid, &cmd->status, 0);
	}
}

void	tree_executor(t_minishell *minishell)
{
	tree_executor_recursive(minishell, NULL, NULL, minishell->root);
	close_pipeline(minishell->root);
	wait_tree(minishell->root);
}
