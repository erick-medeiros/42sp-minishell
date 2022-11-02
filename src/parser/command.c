/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:57:23 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/02 18:46:13 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "structs.h"

t_tree_node	*get_command(t_node **tokens, int num)
{
	t_tree_node	*cmd_node;
	t_token		*token;

	if (*tokens != NULL)
		return (NULL);
	cmd_node = malloc (sizeof(*cmd_node));
	cmd_node->cmd = new_command(num);
	while (*tokens != NULL)
	{
		token = ((t_token *)(*tokens)->content);
		if (token->type == TOKEN_PIPE)
			break ;
		if (token->type == TOKEN_WORD)
			handle_word_token(token, cmd_node);
		*tokens = remove_node(*tokens, del_token_node);
	}
	return (cmd_node);
}

void	handle_word_token(t_token *token, t_tree_node *cmd_node)
{
	(void)token;
	(void)cmd_node;
	return ;
}

