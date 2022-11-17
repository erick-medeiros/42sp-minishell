/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:47:53 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/17 19:26:21 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

static int	create_argv(t_cmd *cmd);

int	command_expansion(t_minishell *ms, t_cmd *cmd)
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
		free(node->content);
		node->content = src;
		src = remove_quote(node->content);
		free(node->content);
		node->content = src;
		node = node->next;
	}
	return (create_argv(cmd));
}

static int	create_argv(t_cmd *cmd)
{
	t_node	*node;
	int		i;

	cmd->argc = 0;
	node = cmd->word_tokens;
	while (node)
	{
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
		cmd->argv[i] = ft_strdup(node->content);
		++i;
		node = node->next;
	}
	cmd->argv[i] = NULL;
	return (0);
}
