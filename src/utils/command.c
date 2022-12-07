/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:36:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 22:02:51 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_command(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->pathname = NULL;
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->envp = NULL;
	cmd->input = STDIN;
	cmd->output = STDOUT;
	cmd->piping[0] = STDIN;
	cmd->piping[1] = STDOUT;
	cmd->redir[0] = STDIN;
	cmd->redir[1] = STDOUT;
	cmd->pid = 0;
	cmd->status = 0;
	cmd->isbuiltin = FALSE;
	cmd->ispipeline = FALSE;
	cmd->redirect = NULL;
	cmd->word_tokens = NULL;
	return (cmd);
}

void	destroy_command(t_cmd *cmd)
{
	int	i;

	if (cmd == NULL)
		return ;
	i = 0;
	while (cmd->argv && cmd->argv[i] && i < cmd->argc + 1)
		free(cmd->argv[i++]);
	clear_list(cmd->redirect, free_token);
	free(cmd->argv);
	free(cmd->pathname);
	free_string_list(cmd->envp);
	clear_list(cmd->word_tokens, free_token);
	free(cmd);
}

void	dup_and_close(t_cmd *cmd)
{
	dup2(cmd->input, STDIN);
	dup2(cmd->output, STDOUT);
	cmd->input = STDIN;
	cmd->output = STDOUT;
	close_safe(cmd->redir[0]);
	close_safe(cmd->redir[1]);
	close_safe(cmd->piping[0]);
	close_safe(cmd->piping[1]);
}
