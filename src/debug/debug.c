/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:16:17 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/19 11:16:25 by eandre-f         ###   ########.fr       */
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
