/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:47:53 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/18 13:13:00 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

static int	create_argv(t_cmd *cmd);
static void	update_content(void **src, void *content);
static int	command_word_expansion(t_minishell *ms, t_cmd *cmd);
static int	command_redirect_expansion(t_minishell *ms, t_cmd *cmd);

int	command_expansion(t_minishell *ms, t_cmd *cmd)
{
	int	status;

	status = command_word_expansion(ms, cmd);
	if (status != 0)
		return (status);
	status = command_redirect_expansion(ms, cmd);
	if (status != 0)
		return (status);
	return (0);
}

static int	command_word_expansion(t_minishell *ms, t_cmd *cmd)
{
	t_node	*node;
	char	*src;

	node = cmd->word_tokens;
	while (node)
	{
		src = parameter_expansion((char *)node->content,
				&ms->env_list, ms->exit_status);
		if (!src)
			return (1);
		update_content(&node->content, src);
		src = remove_quote(node->content);
		if (!src)
			return (1);
		update_content(&node->content, src);
		node = node->next;
	}
	return (create_argv(cmd));
}

static int	command_redirect_expansion(t_minishell *ms, t_cmd *cmd)
{
	t_node	*node;
	t_token	*token;
	char	*src;

	node = cmd->redirect;
	while (node)
	{
		token = node->content;
		src = parameter_expansion(token->value,
				&ms->env_list, ms->exit_status);
		if (!src)
			return (1);
		update_content((void **)&token->value, src);
		src = remove_quote(token->value);
		if (!src)
			return (1);
		update_content((void **)&token->value, src);
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

static void	update_content(void **src, void *content)
{
	if (src)
	{
		free(*src);
		*src = NULL;
		if (content)
			*src = content;
	}
}
