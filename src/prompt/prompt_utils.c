/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 02:43:35 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/03 18:24:23 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static void	execution_process(t_ms *ms);
static char	*get_continue_prompt(int err);

void	process_line(char **line, t_ms *ms)
{
	int		result;
	int		cmd_num;
	char	*history;

	result = ERR_INCOMP_OP;
	cmd_num = 0;
	history = strdup(*line);
	ms->cmd_list.front = NULL;
	ms->cmd_list.rear = NULL;
	while (result > 0 && result != ERR_BAD_SYNTAX
		&& result != ERR_ALLOC)
	{
		lexer(line, &ms->token_list, get_lex_state(result));
		result = parser(ms, cmd_num++);
		result = handle_parse_result(result, line, &history, ms);
	}
	free(*line);
	if (ms->set_history)
		add_history(history);
	free(history);
	if (result == OK)
		execution_process(ms);
}

static void	execution_process(t_ms *ms)
{
	t_tree	*root;

	root = build_tree_postfix(ms);
	free_minishell(ms);
	executor(root, &ms->env_list);
}

int	handle_parse_result(int err, char **line, char **history, t_ms *ms)
{
	t_bool	*interrupted;

	free(*line);
	*line = NULL;
	if (err == ERR_BAD_SYNTAX || err == ERR_ALLOC || err == ERR_BAD_FD)
		ms->env_list.last_status = 2;
	else if (err == ERR_SIGINT)
		ms->env_list.last_status = 130;
	else
	{
		interrupted = init_incomplete();
		if (err >= ERR_INCOMP_OP && err <= ERR_INCOMP_BRC_SQ)
			*line = readline(get_continue_prompt(err));
		handle_signal(SIGINT, prompt_signal_handler);
		if (*interrupted)
		{
			rl_done = FALSE;
			return(ERR_SIGINT);
		}
		ft_strappend(history, "\n");
		ft_strappend(history, *line);
	}
	return (OK);
}

t_lex_state	get_lex_state(int result)
{
	if (result == ERR_INCOMP_DQ || result == ERR_INCOMP_SQ
		|| result == ERR_INCOMP_BRC || result == ERR_INCOMP_BRC_SQ
		|| result == ERR_INCOMP_BRC_DQ)
		return (STATE_CONTINUE);
	return (STATE_SKIP);
}

static char	*get_continue_prompt(int err)
{
	if (err == ERR_INCOMP_OP)
		return (PROMPT_EXTRA_OP);
	if (err == ERR_INCOMP_DQ)
		return (PROMPT_EXTRA_DQ);
	if (err == ERR_INCOMP_SQ)
		return (PROMPT_EXTRA_SQ);
	if (err == ERR_INCOMP_BRC || err == ERR_INCOMP_BRC_SQ
		|| err == ERR_INCOMP_BRC_DQ)
		return (PROMPT_EXTRA_BRC);
	return (PROMPT_CONTINUE);
}
