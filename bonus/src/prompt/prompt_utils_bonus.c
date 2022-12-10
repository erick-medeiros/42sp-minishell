/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 02:43:35 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/10 11:15:59 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "parser_bonus.h"

static char	*get_continue_prompt(int err);
static int	get_line_continuation(char **line, int err);

void	process_line(char **line, t_ms *ms)
{
	int		result;
	char	*history;

	ms->num_pars = 0;
	result = ERR_INCOMP_OP;
	history = strdup(*line);
	ms->cmd_list.front = NULL;
	ms->cmd_list.rear = NULL;
	while (result > 0 && result != ERR_BAD_SYNTAX
		&& result != ERR_ALLOC)
	{
		lexer(line, &ms->token_list, get_lex_state(result));
		result = parser(ms, result);
		result = handle_parse_result(result, line, &history, ms);
	}
	free(*line);
	if (ms->set_history && *history != '\0')
		add_history(history);
	free(history);
	if (result == OK)
		executor(ms);
	else if (result < 0 || result == ERR_ALLOC || result == ERR_BAD_SYNTAX)
		clear_incomplete(&(ms->opstack), &(ms->tmp_cmd));
}

int	handle_parse_result(int err, char **line, char **history, t_ms *ms)
{
	if (err == ERR_BAD_SYNTAX || err == ERR_ALLOC || err == ERR_BAD_FD)
		ms->env_list.last_status = 2;
	else if (err == ERR_SIGINT)
		ms->env_list.last_status = 130;
	else if (err >= ERR_INCOMP_OP && err <= ERR_INCOMP_BRC_SQ)
	{
		if (get_line_continuation(line, err))
		{
			ms->env_list.last_status = 130;
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

static int	get_line_continuation(char **line, int err)
{
	t_bool	*interrupted;

	interrupted = init_incomplete();
	while (*interrupted == FALSE)
	{
		free(*line);
		*line = readline(get_continue_prompt(err));
		if (err == ERR_INCOMP_SQ || err == ERR_INCOMP_DQ
			|| err == ERR_INCOMP_BRC_SQ || err == ERR_INCOMP_BRC_DQ
			|| **line != '\0')
			break ;
	}
	if (*interrupted)
	{
		rl_done = FALSE;
		return (ERR_SIGINT);
	}
	return (OK);
}
