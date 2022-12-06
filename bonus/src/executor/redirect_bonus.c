/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:41:39 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 15:26:53 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_bonus.h"
#include "minishell_bonus.h"

int	command_redirect(t_cmd *cmd)
{
	t_node	*node;
	t_token	*token;

	node = cmd->redirect;
	errno = 0;
	while (node)
	{
		token = node->content;
		if (token->type == TOKEN_INPUT || token->type == TOKEN_HEREDOC)
		{
			close_safe(cmd->redir[0]);
			cmd->redir[0] = open_redir(token->value, token->type);
		}
		else if (token->type == TOKEN_OUTPUT || token->type == TOKEN_APPEND)
		{
			close_safe(cmd->redir[1]);
			cmd->redir[1] = open_redir(token->value, token->type);
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
	int	*p_int;

	permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = -1;
	errno = 0;
	if (token_type == TOKEN_INPUT)
		fd = open(pathname, O_RDONLY);
	else if (token_type == TOKEN_OUTPUT)
		fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, permissions);
	else if (token_type == TOKEN_APPEND)
		fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, permissions);
	else if (token_type == TOKEN_HEREDOC)
	{
		p_int = (int *)pathname;
		fd = *p_int;
	}
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
		command_expansion_to_redirects(cmd, exec->env);
		command_redirect(cmd);
		cmd->group_redir[0] = cmd->redir[0];
		cmd->group_redir[1] = cmd->redir[1];
		cmd->redir[0] = STDIN;
		cmd->redir[1] = STDOUT;
		cmd->redirect = backup;
	}
}

void	define_stds(t_cmd *cmd)
{
	if (cmd->group_redir[0] != STDIN)
		cmd->input = cmd->group_redir[0];
	if (cmd->group_redir[1] != STDOUT)
		cmd->output = cmd->group_redir[1];
	if (cmd->piping[0] != STDIN)
		cmd->input = cmd->piping[0];
	if (cmd->piping[1] != STDOUT)
		cmd->output = cmd->piping[1];
	if (cmd->redir[0] != STDIN)
		cmd->input = cmd->redir[0];
	if (cmd->redir[1] != STDOUT)
		cmd->output = cmd->redir[1];
}
