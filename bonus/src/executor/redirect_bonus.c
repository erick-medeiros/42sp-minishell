/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:41:39 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/21 03:55:20 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "executor_bonus.h"

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
			cmd->input = open_redirect_fd(token->value, token->type);
		}
		else if (token->type == TOKEN_OUTPUT || token->type == TOKEN_APPEND)
		{
			close_safe(cmd->output);
			cmd->output = open_redirect_fd(token->value, token->type);
		}
		if (errno)
			return (error_message(1, (char *[]){
					token->value, strerror(errno), NULL
				}));
		node = node->next;
	}
	return (OK);
}

int	open_redirect_fd(char *pathname, int token_type)
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
