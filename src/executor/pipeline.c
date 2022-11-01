/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:36:07 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/01 19:27:03 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	open_pipes(t_pipeline *pipeline)
{
	int	i;

	pipeline->pipefds = NULL;
	if (pipeline->command_count <= 1)
		return ;
	pipeline->pipefds = malloc(sizeof(int *) * pipeline->command_count);
	if (!pipeline->pipefds)
		panic_error("executor: Error malloc");
	i = 0;
	while (i < pipeline->command_count - 1)
	{
		pipeline->pipefds[i] = malloc(sizeof(int) * 2);
		if (!pipeline->pipefds[i])
			panic_error("executor: Error malloc");
		if (pipe(pipeline->pipefds[i]) < 0)
			panic_error("executor: Error pipe");
		++i;
	}
}

void	connect_pipes(t_pipeline *pipeline, t_cmd *command)
{
	if (pipeline->command_count == 1)
	{
		command->input = STDIN;
		command->output = STDOUT;
	}
	else if (command->number == 0)
	{
		command->input = STDIN;
		command->output = pipeline->pipefds[command->number][1];
	}
	else if (command->number < (pipeline->command_count - 1))
	{
		command->input = pipeline->pipefds[command->number - 1][0];
		command->output = pipeline->pipefds[command->number][1];
	}
	else
	{
		command->input = pipeline->pipefds[command->number - 1][0];
		command->output = STDOUT;
	}
}

void	close_pipes(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < pipeline->command_count - 1)
	{
		close(pipeline->pipefds[i][0]);
		close(pipeline->pipefds[i][1]);
		free(pipeline->pipefds[i]);
		++i;
	}
	free(pipeline->pipefds);
}

void	connect_pipeline(t_cmd *cmd, t_tree *grandparent, t_tree *parent,
			t_tree *node)
{
	int	*pipefd;

	if (parent && parent->left == node)
	{
		pipefd = (int *) parent->content;
		cmd->input = STDIN;
		cmd->output = pipefd[1];
	}
	else if (grandparent && parent && parent->right == node)
	{
		pipefd = (int *) parent->content;
		cmd->input = pipefd[0];
		pipefd = (int *) grandparent->content;
		cmd->output = pipefd[1];
	}
	else if (parent)
	{
		pipefd = (int *) parent->content;
		cmd->input = pipefd[0];
		cmd->output = STDOUT;
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
