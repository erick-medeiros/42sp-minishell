/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:37:24 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 19:31:46 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	expandable_token(t_tok_type type)
{
	return (type != TOKEN_IGNORE && type != TOKEN_HEREDOC);
}

int	convert_tokens_to_argv(t_cmd *cmd)
{
	t_node	*node;
	int		i;

	cmd->argc = 0;
	node = cmd->word_tokens;
	while (node)
	{
		if (((t_token *)node->content)->type == TOKEN_WORD)
			++cmd->argc;
		node = node->next;
	}
	cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!cmd->argv)
		return (1);
	i = 0;
	node = cmd->word_tokens;
	while (node)
	{
		if (((t_token *)node->content)->type == TOKEN_WORD)
			cmd->argv[i++] = ft_strdup(((t_token *)node->content)->value);
		node = node->next;
	}
	cmd->argv[i] = NULL;
	return (0);
}

t_node	*append_list(t_node *node, t_node *append)
{
	t_node	*last;

	last = append;
	while (last && last->next)
		last = last->next;
	last->next = node->next;
	node->next = append;
	return (last);
}
