/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 02:43:35 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/02 17:10:28 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static void	execution_process(t_ms *ms);

void	process_line(char **line, t_ms *ms)
{
	int		parse_result;
	int		cmd_num;
	char	*history;

	parse_result = ERR_INCOMP_OP;
	cmd_num = 0;
	history = strdup(*line);
	ms->cmd_list.front = NULL;
	ms->cmd_list.rear = NULL;
	while (parse_result != OK && parse_result != ERR_BAD_SYNTAX
		&& parse_result != ERR_ALLOC)
	{
		lexer(line, &ms->token_list, get_lex_state(parse_result));
		parse_result = parser(ms, cmd_num++);
		handle_parse_result(parse_result, line, &history, ms);
	}
	free(*line);
	if (ms->set_history)
		add_history(history);
	free(history);
	if (parse_result == OK)
		execution_process(ms);
}

static void	execution_process(t_ms *ms)
{
	t_tree	*root;

	root = build_tree_postfix(ms);
	free_minishell(ms);
	executor(root, &ms->env_list);
}

void	handle_parse_result(int result, char **line, char **history, t_ms *ms)
{
	free(*line);
	*line = NULL;
	if (result == ERR_INCOMP_OP)
		*line = readline(PROMPT_EXTRA_OP);
	else if (result == ERR_INCOMP_DQ)
		*line = readline(PROMPT_EXTRA_DQ);
	else if (result == ERR_INCOMP_SQ)
		*line = readline(PROMPT_EXTRA_SQ);
	else if (result == ERR_INCOMP_BRC || result == ERR_INCOMP_BRC_SQ
		|| result == ERR_INCOMP_BRC_DQ)
		*line = readline(PROMPT_EXTRA_BRC);
	else
	{
		if (result == ERR_BAD_SYNTAX || result == ERR_ALLOC)
			ms->env_list.last_status = 2;
		return ;
	}
	ft_strappend(history, "\n");
	ft_strappend(history, *line);
}

t_lex_state	get_lex_state(int result)
{
	if (result == ERR_INCOMP_DQ || result == ERR_INCOMP_SQ
		|| result == ERR_INCOMP_BRC || result == ERR_INCOMP_BRC_SQ
		|| result == ERR_INCOMP_BRC_DQ)
		return (STATE_CONTINUE);
	return (STATE_SKIP);
}
