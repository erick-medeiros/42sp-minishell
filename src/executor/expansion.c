/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:47:53 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/17 18:11:41 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

int	command_expansion(t_minishell *ms, t_cmd *cmd)
{
	t_node	*node;
	char	*tmp;
	int		i;

	cmd->argc = 0;
	node = cmd->word_tokens;
	while (node)
	{
		++cmd->argc;
		node = node->next;
	}
	cmd->argv = malloc(sizeof(char *) * (cmd->argc + 1));
	node = cmd->word_tokens;
	i = 0;
	while (node)
	{
		tmp = parameter_expansion((char *)node->content,
				&ms->env_list, ms->exit_status);
		cmd->argv[i] = remove_quote(tmp);
		free(tmp);
		++i;
		node = node->next;
	}
	cmd->argv[i] = NULL;
	return (0);
}
