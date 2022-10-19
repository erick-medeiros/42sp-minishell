/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:31 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/19 11:17:23 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*lexer(char *prompt)
{
	char	**cmd;
	size_t	i;
	t_node	*list;
	t_token	*token;

	cmd = ft_split_cmd(prompt, ' ');
	list = NULL;
	i = 0;
	while (cmd[i])
	{
		token = malloc(sizeof(t_token));
		token->value = ft_strdup(cmd[i]);
		token->type = TOKEN_WORD;
		if (ft_strcmp(token->value, "|") == 0)
			token->type = TOKEN_PIPE;
		else if (ft_strcmp(token->value, "<") == 0)
			token->type = TOKEN_INPUT;
		else if (ft_strcmp(token->value, ">") == 0)
			token->type = TOKEN_OUTPUT;
		else if (ft_strcmp(token->value, ">>") == 0)
			token->type = TOKEN_APPEND;
		add_node(&list, token);
		free(cmd[i]);
		++i;
	}
	free(cmd);
	return (list);
}
