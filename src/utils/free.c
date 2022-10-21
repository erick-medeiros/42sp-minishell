/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:38:19 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/20 19:08:07 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}

void	free_command(void *content)
{
	t_command	*cmd;
	int			i;

	cmd = (t_command *) content;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		free(cmd->argv[i]);
		++i;
	}
	free(cmd->argv);
	free(cmd->pathname);
	free(cmd);
}

void	free_pipeline(void *content)
{
	t_pipeline	*pipeline;

	pipeline = (t_pipeline *)content;
	clear_list(pipeline->commands, free_command);
	free(pipeline);
}

void	free_minishell(t_minishell *minishell)
{
	clear_list(minishell->pipelines, free_pipeline);
	clear_list(minishell->token_list, free_token);
	free_string_list(minishell->path_list);
}

void	free_string_list(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
