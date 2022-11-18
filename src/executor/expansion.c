/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:47:53 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/18 14:08:27 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

static int	create_argv(t_cmd *cmd);
static int	expand_token(char **src, char *content, t_minishell *ms);

int	command_expansion(t_minishell *ms, t_cmd *cmd)
{
	t_token	*token;
	t_node	*node;

	node = cmd->word_tokens;
	while (node)
	{
		if (expand_token((char **)&node->content, node->content, ms) != 0)
			return (1);
		node = node->next;
	}
	if (create_argv(cmd) != 0)
		return (1);
	node = cmd->redirect;
	while (node)
	{
		token = node->content;
		if (expand_token(&token->value, token->value, ms) != 0)
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
		if (ft_strlen(node->content) > 0)
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
		if (ft_strlen(node->content) > 0)
			cmd->argv[i++] = ft_strdup(node->content);
		node = node->next;
	}
	cmd->argv[i] = NULL;
	return (0);
}

static int	expand_token(char **src, char *content, t_minishell *ms)
{
	char	*tmp;

	tmp = parameter_expansion(content, &ms->env_list, ms->exit_status);
	if (!tmp)
		return (1);
	content = tmp;
	tmp = remove_quote(content);
	free(content);
	if (!tmp)
		return (1);
	*src = tmp;
	return (0);
}
