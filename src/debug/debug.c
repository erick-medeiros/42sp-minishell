/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:16:17 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/19 18:33:29 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	debug_token(t_minishell *minishell)
{
	t_node	*node;
	t_token	*token;
	char	*types[7];

	types[0] = "TOKEN_WORD";
	types[1] = "TOKEN_PIPE";
	types[2] = "TOKEN_INPUT";
	types[3] = "TOKEN_OUTPUT";
	types[4] = "TOKEN_APPEND";
	types[5] = "TOKEN_SQUOTE";
	types[6] = "TOKEN_DQUOTE";
	node = minishell->token_list;
	printf("token list:\n");
	while (node)
	{
		token = node->content;
		printf("value (%s) type (%s)\n", token->value, types[token->type]);
		node = node->next;
	}
}

// debug return heredoc and endsinpipe
void	debug_content_fd(int fd, char *prompt, int debug)
{
	char	*content;

	content = get_content_fd(fd);
	if (debug == 1)
		printf("%s", content);
	else
		printf("exec: %s %s\n", prompt, content);
	free(content);
	close(fd);
}
