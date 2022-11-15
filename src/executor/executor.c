/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 18:08:54 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtins.h"
#include "structs.h"

void	executor(t_minishell *minishell)
{
	tree_executor(minishell, NULL, NULL, minishell->root);
	close_pipeline(minishell->root);
	sync_tree_execution(minishell->root, &minishell->exit_status);
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

void	sync_tree_execution(t_tree *root, int *exit_status)
{
	t_cmd	*cmd;

	if (!root)
		return ;
	if (root->left)
		sync_tree_execution(root->left, exit_status);
	if (root->right)
		sync_tree_execution(root->right, exit_status);
	if (root->type == TREE_TYPE_CMD)
	{
		cmd = (t_cmd *) root->content;
		if (cmd->pid > 0)
			process_exit_status(cmd);
		*exit_status = cmd->status;
	}
}

void	process_exit_status(t_cmd *command)
{
	waitpid(command->pid, &command->status, 0);
	if (WIFEXITED(command->status))
		command->status = WEXITSTATUS(command->status);
	else if (WIFSIGNALED(command->status))
		command->status = WTERMSIG(command->status);
}

int	execute_command(t_minishell *minishell, t_cmd *command)
{
	command_search(command, &minishell->env_list);
	if (command->isbuiltin && !minishell->pipeline)
		command->status = execute_builtin(minishell, command);
	else
		subshell(minishell, command);
	return (0);
}
