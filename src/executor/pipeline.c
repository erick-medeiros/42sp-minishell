/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:36:07 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 08:37:34 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

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
