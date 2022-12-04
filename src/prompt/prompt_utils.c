/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 02:43:35 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/03 22:33:50 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static char	*get_continue_prompt(int err);
static void	get_continuation(char **line, int err);

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
		executor(ms);
	else if (result < 0 || result == ERR_ALLOC)
		clear_incomplete(&(ms->opstack), &(ms->tmp_cmd));
}

int	handle_parse_result(int err, char **line, char **history, t_ms *ms)
{
	t_bool	*interrupted;

	if (err == ERR_BAD_SYNTAX || err == ERR_ALLOC || err == ERR_BAD_FD)
		ms->env_list.last_status = 2;
	else if (err == ERR_SIGINT)
		ms->env_list.last_status = 130;
	else if (err >= ERR_INCOMP_OP && err <= ERR_INCOMP_BRC_SQ)
	{
		interrupted = init_incomplete();
		get_continuation(line, err);
		handle_signal(SIGINT, prompt_signal_handler);
		if (*interrupted)
		{
			rl_done = FALSE;
			return (ERR_SIGINT);
		}
		if (err == ERR_INCOMP_SQ || err == ERR_INCOMP_DQ
			|| err == ERR_INCOMP_BRC_SQ || err == ERR_INCOMP_BRC_DQ)
			ft_strappend(history, "\n");
		else
			ft_strappend(history, " ");
		ft_strappend(history, *line);
	}
	return (err);
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

static void	get_continuation(char **line, int err)
{
	while (TRUE)
	{
		free(*line);
		*line = readline(get_continue_prompt(err));
		if (err == ERR_INCOMP_SQ || err == ERR_INCOMP_DQ
			|| err == ERR_INCOMP_BRC_SQ || err == ERR_INCOMP_BRC_DQ
			|| **line != '\0')
			break ;
	}
}
