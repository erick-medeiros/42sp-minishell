/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:41:39 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/08 19:44:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_bonus.h"
#include "minishell_bonus.h"

static int	open_redir(t_token *token, int close_fd);

int	command_redirect(t_cmd *cmd, t_vlst *env)
{
	t_node	*node;
	t_token	*token;

	cmd->status = command_expansion_to_redirects(cmd, env);
	if (cmd->status != OK)
		return (cmd->status);
	node = cmd->redirect;
	while (node)
	{
		token = node->content;
		if (token->type == TOKEN_INPUT || token->type == TOKEN_HEREDOC)
		{
			cmd->input = open_redir(token, cmd->input);
			if (cmd->input == -1 && errno)
				return (error_message2(1, token->value, strerror(errno)));
		}
		else if (token->type == TOKEN_OUTPUT || token->type == TOKEN_APPEND)
		{
			cmd->output = open_redir(token, cmd->output);
			if (cmd->output == -1 && errno)
				return (error_message2(1, token->value, strerror(errno)));
		}
		node = node->next;
	}
	return (OK);
}

static int	open_redir(t_token *token, int close_fd)
{
	int	fd;
	int	permissions;
	int	*p_int;

	close_safe(close_fd);
	permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = -1;
	errno = 0;
	if (token->type == TOKEN_INPUT)
		fd = open(token->value, O_RDONLY);
	else if (token->type == TOKEN_OUTPUT)
		fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, permissions);
	else if (token->type == TOKEN_APPEND)
		fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, permissions);
	else if (token->type == TOKEN_HEREDOC)
	{
		p_int = (int *)token->value;
		fd = *p_int;
	}
	return (fd);
}
