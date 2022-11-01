/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:20:55 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/01 19:37:44 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	destroy_exec_tree(t_tree *root)
{
	if (root->type == TREE_TYPE_CMD)
		destroy_command(root->content);
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

void	tree_subshell(t_minishell *minishell, t_cmd *command)
{
	command->pid = fork();
	if (command->pid < 0)
		panic_error("executor: fork");
	else if (command->pid == 0)
	{
		command->input = dup(command->input);
		command->output = dup(command->output);
		subshell_redirect(minishell, command);
		close_pipeline(minishell->root);
		if (command->isbuiltin)
		{
			builtins(minishell, command);
			destroy_tree(minishell->root, destroy_exec_tree);
			exit_subshell(minishell, 0);
		}
		else
			execute_program(minishell, command);
		destroy_tree(minishell->root, destroy_exec_tree);
		exit_subshell(minishell, 0);
	}
}

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
		tree_subshell(minishell, cmd);
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

void	tree_executor(t_minishell *minishell, t_pipeline *pipeline)
{
	minishell->root = convert_list_to_tree(pipeline);
	tree_executor_recursive(minishell, NULL, NULL, minishell->root);
	close_pipeline(minishell->root);
	wait_tree(minishell->root);
	destroy_tree(minishell->root, destroy_exec_tree);
}
