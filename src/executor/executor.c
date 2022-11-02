/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 11:50:00 by eandre-f         ###   ########.fr       */
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
	sync_tree_execution(minishell->root);
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
	if (root->type == TREE_TYPE_CMD)
	{
		cmd = (t_cmd *) root->content;
		if (cmd->isbuiltin)
			builtins(minishell, cmd);
		else
		{
			connect_pipeline(cmd, grandparent, parent, root);
			subshell(minishell, cmd);
		}
	}
}

void	sync_tree_execution(t_tree *root)
{
	t_cmd	*cmd;

	if (!root)
		return ;
	if (root->left)
		sync_tree_execution(root->left);
	if (root->right)
		sync_tree_execution(root->right);
	if (root->type == TREE_TYPE_CMD)
	{
		cmd = (t_cmd *) root->content;
		if (cmd->subshell)
			waitpid(cmd->pid, &cmd->status, 0);
	}
}

void	builtins(t_minishell *minishell, t_cmd *command)
{
	if (command_is_equal(command->pathname, "echo"))
		builtin_echo(command);
	else if (command_is_equal(command->pathname, "cd") && command->argc == 2)
		builtin_cd(command->argv[1], &minishell->env_list);
	else if (command_is_equal(command->pathname, "pwd"))
		builtin_pwd();
	else if (command_is_equal(command->pathname, "export"))
		builtin_export(command->argc, command->argv, &minishell->env_list);
	else if (command_is_equal(command->pathname, "unset"))
		builtin_unset(command->argc, command->argv, &minishell->env_list);
	else if (command_is_equal(command->pathname, "env"))
		builtin_env(&minishell->env_list);
	else if (command_is_equal(command->pathname, "exit"))
	{
		destroy_minishell(minishell);
		builtin_exit();
	}
}

void	process_exit_status(t_cmd *command)
{
	if (WIFEXITED(command->status))
		command->status = WEXITSTATUS(command->status);
}
