/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:41:39 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/07 15:18:46 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

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

void	define_stds(t_cmd *cmd)
{
	if (cmd->piping[0] != STDIN)
		cmd->input = cmd->piping[0];
	if (cmd->piping[1] != STDOUT)
		cmd->output = cmd->piping[1];
	if (cmd->redir[0] != STDIN)
		cmd->input = cmd->redir[0];
	if (cmd->redir[1] != STDOUT)
		cmd->output = cmd->redir[1];
}

void	close_command_redirects(t_cmd *cmd)
{
	close_safe(cmd->piping[0]);
	close_safe(cmd->piping[1]);
	cmd->piping[0] = -1;
	cmd->piping[1] = -1;
	close_safe(cmd->redir[0]);
	close_safe(cmd->redir[1]);
	cmd->redir[0] = -1;
	cmd->redir[1] = -1;
}
