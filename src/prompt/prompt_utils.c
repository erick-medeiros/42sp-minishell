/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 02:43:35 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/15 01:02:48 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"

void	process_line(char **line, t_minishell *minishell)
{
	int			parse_result;
	int			cmd_num;
	char		*history;

	parse_result = ERR_INCOMP_PIPE;
	cmd_num = 0;
	history = strdup(*line);
	minishell->cmd_list.front = NULL;
	minishell->cmd_list.rear = NULL;
	while (parse_result != OK && parse_result != ERR_BAD_SYNTAX
		&& parse_result != ERR_ALLOC)
	{
		lexer(line, &minishell->token_list, get_lex_state(parse_result));
		parse_result = parser(minishell, cmd_num++);
		handle_parse_result(parse_result, line, &history, minishell);
	}
	free(*line);
	if (minishell->set_history)
		add_history(history);
	free(history);
	if (parse_result == OK)
	{
		minishell->root = build_tree_postfix(minishell);
		executor(minishell);
	}
}

void	handle_parse_result(int result, char **line,
			char **history, t_minishell *ms)
{
	if (result == ERR_BAD_SYNTAX || result == ERR_ALLOC)
		print_parse_error(result);
	if (ms->heredoc_queue.front)
	{
		ms->set_history = FALSE;
		process_heredoc(&ms->heredoc_queue);
	}
	free(*line);
	*line = NULL;
	if (result == ERR_INCOMP_PIPE)
		*line = readline(PROMPT_EXTRA_PIPE);
	else if (result == ERR_INCOMP_DQ)
		*line = readline(PROMPT_EXTRA_DQ);
	else if (result == ERR_INCOMP_SQ)
		*line = readline(PROMPT_EXTRA_SQ);
	else if (result == ERR_INCOMP_BRC || result == ERR_INCOMP_BRC_SQ
		|| result == ERR_INCOMP_BRC_DQ)
		*line = readline(PROMPT_EXTRA_BRC);
	else
		return ;
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

int	print_parse_error(int parse_result)
{
	if (parse_result == ERR_BAD_SYNTAX)
		write(STDERR, MSG_SYNTAX_ERR, ft_strlen(MSG_SYNTAX_ERR));
	else if (parse_result == ERR_ALLOC)
		write(STDERR, MSG_ALLOC_ERR, ft_strlen(MSG_ALLOC_ERR));
	write(STDERR, "\n", 1);
	return (parse_result);
}
