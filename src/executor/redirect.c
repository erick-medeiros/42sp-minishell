/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:41:39 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/30 12:15:45 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

int	command_redirect(t_cmd *cmd)
{
	t_node	*node;
	t_token	*token;

	node = cmd->redirect;
	while (node)
	{
		token = node->content;
		if (token->type == TOKEN_INPUT)
		{
			close_safe(cmd->input);
			cmd->input = open_redir(token->value, token->type);
		}
		else if (token->type == TOKEN_OUTPUT || token->type == TOKEN_APPEND)
		{
			close_safe(cmd->output);
			cmd->output = open_redir(token->value, token->type);
		}
		if (errno)
			return (error_message2(1, token->value, strerror(errno)));
		node = node->next;
	}
	return (OK);
}

int	open_redir(char *pathname, int token_type)
{
	int	fd;
	int	permissions;

	permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = -1;
	errno = 0;
	if (token_type == TOKEN_INPUT)
		fd = open(pathname, O_RDONLY);
	else if (token_type == TOKEN_OUTPUT)
		fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, permissions);
	else if (token_type == TOKEN_APPEND)
		fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, permissions);
	return (fd);
}

void	redirect_command_list(t_exec *exec, t_tree *root, t_node *redir)
{
	t_cmd	*cmd;
	t_node	*backup;

	if (!root)
		return ;
	if (root->left)
		redirect_command_list(exec, root->left, redir);
	if (root->right)
		redirect_command_list(exec, root->right, redir);
	if (root->type == TREE_TYPE_CMD)
	{
		cmd = root->content;
		backup = cmd->redirect;
		cmd->redirect = redir;
		expand_redirects(cmd->redirect, exec->env);
		command_redirect(cmd);
		cmd->redirect = backup;
	}
}

void	update_command_input(t_cmd *cmd, int new_input)
{
	close_safe(cmd->input);
	cmd->input = new_input;
}

void	update_command_output(t_cmd *cmd, int new_output)
{
	close_safe(cmd->output);
	cmd->output = new_output;
}
