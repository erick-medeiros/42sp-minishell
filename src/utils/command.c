/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:36:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/07 22:59:33 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
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
	cmd->pid = 0;
	cmd->status = 0;
	cmd->isbuiltin = FALSE;
	cmd->subshell = FALSE;
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
	close_safe(cmd->input);
	close_safe(cmd->output);
	free(cmd);
}
