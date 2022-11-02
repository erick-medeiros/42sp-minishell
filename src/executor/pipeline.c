/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:36:07 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 18:41:39 by eandre-f         ###   ########.fr       */
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

int	open_redirects(t_node *redirects)
{
	int			fd;
	int			mode;
	t_node		*node;
	t_redirect	*redirect;

	fd = -1;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	node = redirects;
	while (node)
	{
		fd = -1;
		redirect = ((t_redirect *)node->content);
		if (redirect->operator == TOKEN_INPUT)
			fd = open(redirect->path, O_RDONLY);
		else if (redirect->operator == TOKEN_OUTPUT)
			fd = open(redirect->path, O_WRONLY | O_CREAT | O_TRUNC, mode);
		else if (redirect->operator == TOKEN_APPEND)
			fd = open(redirect->path, O_WRONLY | O_CREAT | O_APPEND, mode);
		node = node->next;
		if (node)
			close(fd);
	}
	return (fd);
}
