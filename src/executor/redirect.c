/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:41:39 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/16 21:01:40 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	command_redirect(t_cmd *cmd)
{
	t_node	*node;
	t_token	*token;
	int		fd;

	node = cmd->redirect;
	while (node)
	{
		token = node->content;
		fd = open_redirect_fd(token->value, token->type);
		if (errno)
			return (error_message(1, (char *[]){
					token->value, strerror(errno), NULL
				}));
		if (token->type == TOKEN_INPUT)
			cmd->input = fd;
		else if (token->type == TOKEN_OUTPUT)
			cmd->output = fd;
		else if (token->type == TOKEN_APPEND)
			cmd->output = fd;
		node = node->next;
		if (node)
			close(fd);
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
