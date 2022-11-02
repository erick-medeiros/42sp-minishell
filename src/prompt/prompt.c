/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 18:42:44 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "minishell.h"
#include "parser.h"


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
	int		complete;
	t_node	*heredoc_queue;
	int		parse_result;

	complete = 0;
	heredoc_queue = NULL;
	while (!complete)
	{
		lexer(prompt, &minishell->token_list, STATE_SKIP);
		parse_result = parser(minishell, &heredoc_queue);
		if (parse_result == ERR_BAD_SYNTAX)
			print_parse_error(parse_result);
		// if (heredoc_queue)
		// 	process_heredoc(&heredoc_queue);
		else
			add_history(prompt);
		free(prompt);
	}
	executor(minishell);
}

void		print_parse_error(int parse_result)
{
	if (parse_result == ERR_BAD_SYNTAX)
		printf("%s\n", MSG_SYNTAX_ERR);
	return ;
}

