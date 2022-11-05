/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/05 03:57:16 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"

static t_lex_state	get_lex_state(int parse_result);
static void			handle_parse_result(int result, char **prompt,
						char **history, t_minishell *minishell);

void	miniprompt(t_minishell *minishell)
{
	char	*prompt;

	while (1)
	{
		prompt = readline(PROMPT_STRING);
		if (!prompt)
			break ;
		minishell->token_list = NULL;
		process_line(prompt, minishell);
		free_minishell(minishell);
	}
	free(prompt);
}

void	process_line(char *prompt, t_minishell *minishell)
{
	int		parse_result;
	int		cmd_num;
	char	*history;

	parse_result = ERR_INCOMP_PIPE;
	cmd_num = 0;
	history = strdup(prompt);
	while (parse_result != OK && parse_result != ERR_BAD_SYNTAX
		&& parse_result != ERR_ALLOC)
	{
		lexer(prompt, &minishell->token_list, get_lex_state(parse_result));
		parse_result = parser(minishell, cmd_num++);
		handle_parse_result(parse_result, &prompt, &history, minishell);
	}
	free(prompt);
	add_history(history);
	free(history);
	if (parse_result == OK)
		executor(minishell);
}

static void	handle_parse_result(int result, char **prompt,
			char **history, t_minishell *ms)
{
	if (result == ERR_BAD_SYNTAX || result == ERR_ALLOC)
		print_parse_error(result);
	if (ms->heredoc_queue.front)
		process_heredoc(&ms->heredoc_queue);
	free(*prompt);
	*prompt = NULL;
	if (result == ERR_INCOMP_PIPE)
		*prompt = readline(PROMPT_EXTRA_PIPE);
	else if (result == ERR_INCOMP_DQ)
		*prompt = readline(PROMPT_EXTRA_DQ);
	else if (result == ERR_INCOMP_SQ)
		*prompt = readline(PROMPT_EXTRA_PIPE);
	else
		return ;
	ft_strappend(history, *prompt);
}

static t_lex_state	get_lex_state(int parse_result)
{
	if (parse_result == ERR_INCOMP_DQ)
		return (STATE_DQUOTE);
	if (parse_result == ERR_INCOMP_SQ)
		return (STATE_SQUOTE);
	return (STATE_SKIP);
}

int	print_parse_error(int parse_result)
{
	if (parse_result == ERR_BAD_SYNTAX)
		printf("%s\n", MSG_SYNTAX_ERR);
	else if (parse_result == ERR_ALLOC)
		printf("%s\n", MSG_ALLOC_ERR);
	return (parse_result);
}
