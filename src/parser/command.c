/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:57:23 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/31 02:30:41 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

static int	is_cmd_part(t_tok_type tok_type);

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
			return (cmd_node);
		if (token->type == TOKEN_WORD)

		*tokens = remove_node(*tokens, del_token_node);
	}
}
