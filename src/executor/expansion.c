/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:47:53 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/19 14:21:04 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
#include "minishell.h"

static int	create_argv(t_cmd *cmd);
static int	expand_token(t_token **token, t_vlst *env);

int	command_expansion(t_cmd *cmd, t_vlst *env)
{
	t_token	*token;
	t_node	*node;

	node = cmd->word_tokens;
	while (node)
	{
		token = node->content;
		if (expand_token(&token, env) != 0)
			return (1);
		node = node->next;
	}
	if (create_argv(cmd) != 0)
		return (1);
	node = cmd->redirect;
	while (node)
	{
		token = node->content;
		if (expand_token(&token, env) != 0)
			return (1);
		node = node->next;
	}
	return (0);
}

static int	create_argv(t_cmd *cmd)
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

static int	expand_token(t_token **token, t_vlst *env)
{
	char	*tmp;
	char	*content;

	content = (*token)->value;
	tmp = parameter_expansion(content, env);
	if (!tmp)
		return (1);
	if (!ft_streq(content, tmp) && ft_strlen(tmp) == 0
		&& (*token)->type == TOKEN_WORD)
		(*token)->type = TOKEN_IGNORE;
	free(content);
	content = tmp;
	tmp = expand_filename(content);
	free(content);
	if (!tmp)
		return (1);
	content = tmp;
	tmp = remove_quote(content);
	free(content);
	if (!tmp)
		return (1);
	(*token)->value = tmp;
	return (0);
}
