/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:36:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 15:22:11 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
	cmd->group_redir[0] = STDIN;
	cmd->group_redir[1] = STDOUT;
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
	close_safe(cmd->redir[0]);
	close_safe(cmd->redir[1]);
	close_safe(cmd->piping[0]);
	close_safe(cmd->piping[1]);
	close_safe(cmd->group_redir[0]);
	close_safe(cmd->group_redir[1]);
	free(cmd);
}
