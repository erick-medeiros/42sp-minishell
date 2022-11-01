/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:20:55 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/01 17:25:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	destroy_exec_tree(t_tree *root)
{
	if (root->type == TREE_TYPE_CMD)
		destroy_command(root->content);
}

void	close_pipes_tree(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
		close_pipes_tree(root->left);
	if (root->right)
		close_pipes_tree(root->right);
	if (root->type == TREE_TYPE_PIPE)
	{
		close(((int *)root->content)[0]);
		close(((int *)root->content)[1]);
		free(root->content);
	}
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
		command = duplicate_command(command);
		subshell_redirect(minishell, command);
		close_pipes_tree(minishell->root);
		destroy_tree(minishell->root, destroy_exec_tree);
		if (command->isbuiltin)
		{
			builtins(minishell, command);
			destroy_command(command);
			exit_subshell(minishell, 0);
		}
		else
			execute_program(minishell, command);
		destroy_command(command);
		exit_subshell(minishell, 0);
	}
}

void	tree_io(t_cmd *cmd, t_tree *parent_parent, t_tree *parent, t_tree *tree_node)
{
	int	*pipefd;

	if (parent && parent->left == tree_node)
	{
		pipefd = (int *) parent->content;
		cmd->input = STDIN;
		cmd->output = pipefd[1];
	}
	else if (parent_parent && parent && parent->right == tree_node)
	{
		pipefd = (int *) parent->content;
		cmd->input = pipefd[0];
		pipefd = (int *) parent_parent->content;
		cmd->output = pipefd[1];
	}
	else if (parent)
	{
		pipefd = (int *) parent->content;
		cmd->input = pipefd[0];
		cmd->output = STDOUT;
	}
}

void	tree_executor_recursive(t_minishell *minishell, t_tree *parent_parent, t_tree *parent, t_tree *tree_node)
{
	t_cmd	*cmd;

	if (tree_node->type == TREE_TYPE_PIPE)
	{
		tree_node->content = malloc(sizeof(int) * 2);
		if (pipe(tree_node->content) == -1)
			panic_error("tree executor ~ pipe");
	}
	if (tree_node->left)
		tree_executor_recursive(minishell, parent, tree_node, tree_node->left);
	if (tree_node->right)
		tree_executor_recursive(minishell, parent, tree_node, tree_node->right);
	if (tree_node->type == TREE_TYPE_CMD)
	{
		cmd = (t_cmd *) tree_node->content;
		tree_io(cmd, parent_parent, parent, tree_node);
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
	if (minishell->root)
		tree_executor_recursive(minishell, NULL, NULL, minishell->root);
	close_pipes_tree(minishell->root);
	wait_tree(minishell->root);
	destroy_tree(minishell->root, destroy_exec_tree);
}
