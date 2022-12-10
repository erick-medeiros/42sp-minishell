/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 17:19:38 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/10 10:33:17 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "parser.h"

void	init_minishell(t_ms *ms, char **envp)
{
	ms->token_list = NULL;
	ms->env_list.len = 0;
	ms->env_list.list = NULL;
	ms->cmd_list.front = NULL;
	ms->cmd_list.rear = NULL;
	ms->tmp_cmd = NULL;
	ms->opstack = NULL;
	ms->set_history = TRUE;
	ms->env_list.last_status = 0;
	if (envp)
		envp_to_list(envp, &ms->env_list);
}

void	clear_minishell(t_ms *ms)
{
	if (ms->token_list)
	{
		clear_list(ms->token_list, free_token);
		ms->token_list = NULL;
	}
	if (ms->cmd_list.front)
	{
		clear_list(ms->cmd_list.front, del_cmd_tree_node);
		ms->cmd_list.front = NULL;
		ms->cmd_list.rear = NULL;
	}
}

void	destroy_minishell(t_ms *ms)
{
	clear_minishell(ms);
	if (ms->env_list.list)
		clear_list(ms->env_list.list, del_var_node);
	rl_clear_history();
}

void	shell(t_ms *ms, char **line)
{
	ms->set_history = FALSE;
	process_line(line, ms);
	clear_minishell(ms);
}

void	shell_loop(t_ms *ms)
{
	char	*line;
	t_bool	*sigint;

	while (1)
	{
		handle_signal(SIGQUIT, SIG_IGN);
		handle_signal(SIGPIPE, SIG_IGN);
		sigint = init_incomplete();
		ms->set_history = TRUE;
		line = readline(get_prompt(&ms->env_list));
		if (*sigint)
		{
			ms->env_list.last_status = 130;
			free(line);
			continue ;
		}
		if (!line)
		{
			write(STDOUT, "exit\n", 5);
			break ;
		}
		process_line(&line, ms);
		clear_minishell(ms);
	}
}
