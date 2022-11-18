/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/18 12:23:26 by eandre-f         ###   ########.fr       */
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
	if (ms->exit_status == OK)
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

int	command_exit_status(t_cmd *cmd, int *coredump)
{
	if (cmd->pid > 0 && cmd->status == 0)
	{
		waitpid(cmd->pid, &cmd->status, 0);
		if (WIFEXITED(cmd->status))
			cmd->status = WEXITSTATUS(cmd->status);
		else if (WIFSIGNALED(cmd->status))
		{
			if (coredump)
				*coredump = WCOREDUMP(cmd->status);
			cmd->status = 128 + WTERMSIG(cmd->status);
		}
	}
	return (cmd->status);
}

int	execute_command(t_minishell *ms, t_cmd *cmd)
{
	int	result;

	cmd->status = command_expansion(ms, cmd);
	if (cmd->status != OK)
		return (cmd->status);
	if (cmd->argc == 0)
		return (0);
	cmd->status = command_redirect(cmd);
	if (cmd->status != OK)
		return (cmd->status);
	result = command_search(cmd, &ms->env_list);
	if (result != OK && result != ERR_CMD_NOT_FOUND)
		return (set_exit_code(ms, result));
	if (cmd->isbuiltin && !ms->pipeline)
		cmd->status = execute_builtin(ms, cmd);
	else
		subshell(ms, cmd);
	return (0);
}
