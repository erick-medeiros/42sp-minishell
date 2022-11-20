/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/19 14:01:23 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
#include "minishell.h"

void	executor(t_minishell *ms)
{
	int	coredump;

	coredump = 0;
	tree_executor(ms, ms->root, STDIN, STDOUT);
	sync_tree_execution(ms->root, (&ms->env_list.last_status), &coredump);
	print_signal_error((ms->env_list.last_status), coredump);
}

void	tree_executor(t_minishell *ms, t_tree *root, int input, int output)
{
	t_cmd	*cmd;
	int		*pipefd;

	if (!root)
		return ;
	if (root->type == TREE_TYPE_PIPE)
	{
		root->content = malloc(sizeof(int) * 2);
		if (pipe(root->content) == -1)
			error_message2(1, "pipe failed", strerror(errno));
		pipefd = (int *)root->content;
		if (root->left)
			tree_executor(ms, root->left, input, pipefd[WRITE_PIPE]);
		close(pipefd[WRITE_PIPE]);
		if (root->right)
			tree_executor(ms, root->right, pipefd[READ_PIPE], output);
		close(pipefd[READ_PIPE]);
	}
	if (root->type != TREE_TYPE_CMD)
		return ;
	cmd = (t_cmd *) root->content;
	cmd->input = input;
	cmd->output = output;
	execute_command(ms, cmd, &ms->env_list);
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
