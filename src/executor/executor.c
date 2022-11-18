/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/18 19:10:33 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
#include "minishell.h"

void	executor(t_minishell *ms)
{
	int	coredump;

	coredump = 0;
	tree_executor(ms, NULL, NULL, ms->root);
	close_pipeline(ms->root);
	sync_tree_execution(ms->root, &ms->exit_status, &coredump);
	print_signal_error(ms->exit_status, coredump);
}

void	tree_executor(t_minishell *minishell, t_tree *grandparent,
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
		tree_executor(minishell, parent, root, root->left);
	if (root->right)
		tree_executor(minishell, parent, root, root->right);
	if (root->type != TREE_TYPE_CMD)
		return ;
	cmd = (t_cmd *) root->content;
	connect_pipeline(cmd, grandparent, parent, root);
	execute_command(minishell, cmd);
}

void	sync_tree_execution(t_tree *root, int *status, int *coredump)
{
	if (!root)
		return ;
	if (root->left)
		sync_tree_execution(root->left, status, coredump);
	if (root->right)
		sync_tree_execution(root->right, status, coredump);
	if (root->type == TREE_TYPE_CMD)
		*status = command_exit_status(root->content, coredump);
}

void	connect_pipeline(t_cmd *cmd, t_tree *grandparent, t_tree *parent,
			t_tree *node)
{
	int	*pipefd;

	if (parent && parent->left == node)
	{
		pipefd = (int *) parent->content;
		cmd->piping[READ_PIPE] = STDIN;
		cmd->piping[WRITE_PIPE] = pipefd[1];
	}
	else if (grandparent && parent && parent->right == node)
	{
		pipefd = (int *) parent->content;
		cmd->piping[READ_PIPE] = pipefd[0];
		pipefd = (int *) grandparent->content;
		cmd->piping[WRITE_PIPE] = pipefd[1];
	}
	else if (parent)
	{
		pipefd = (int *) parent->content;
		cmd->piping[READ_PIPE] = pipefd[0];
		cmd->piping[WRITE_PIPE] = STDOUT;
	}
}

void	close_pipeline(t_tree *root)
{
	if (!root)
		return ;
	if (root->left)
		close_pipeline(root->left);
	if (root->right)
		close_pipeline(root->right);
	if (root->type == TREE_TYPE_PIPE)
	{
		close(((int *)root->content)[0]);
		close(((int *)root->content)[1]);
		free(root->content);
	}
}
