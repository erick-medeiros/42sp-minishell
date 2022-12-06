/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:47:53 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 19:28:51 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
#include "minishell.h"

t_bool		ignore_token(t_tok_type type);
static int	shell_expansion_parameter(t_node **tokens, t_vlst *env);
static int	shell_expansion_quote_removal(t_node **tokens);
//

int	command_expansion_to_words(t_cmd *cmd, t_vlst *env)
{
	if (shell_expansion_parameter(&cmd->word_tokens, env) != 0)
		return (1);
	if (shell_expansion_quote_removal(&cmd->word_tokens) != 0)
		return (1);
	return (0);
}

int	command_expansion_to_redirects(t_cmd *cmd, t_vlst *env)
{
	if (shell_expansion_parameter(&cmd->redirect, env) != 0)
		return (1);
	if (shell_expansion_quote_removal(&cmd->redirect) != 0)
		return (1);
	return (0);
}

static int	shell_expansion_parameter(t_node **tokens, t_vlst *env)
{
	t_node	*node;
	t_token	*token;
	char	*tmp;

	node = *tokens;
	while (node)
	{
		token = node->content;
		if (expandable_token(token->type))
		{
			tmp = parameter_expansion(token->value, env);
			if (!tmp)
				return (1);
			if (!ft_streq(token->value, tmp) && ft_strlen(tmp) == 0
				&& token->type == TOKEN_WORD)
				token->type = TOKEN_IGNORE;
			ft_strupd(&token->value, tmp);
		}
		node = node->next;
	}
	return (0);
}

static int	shell_expansion_quote_removal(t_node **tokens)
{
	t_node	*node;
	t_token	*token;

	node = *tokens;
	while (node)
	{
		token = node->content;
		if (expandable_token(token->type))
			ft_strupd(&token->value, remove_quote(token->value));
		node = node->next;
	}
	return (0);
}
