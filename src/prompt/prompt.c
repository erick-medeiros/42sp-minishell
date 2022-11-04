/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/04 16:18:24 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "minishell.h"

void	temp_call(char *prompt)
{
	int	fd;

	if (command_is_equal(prompt, "here_doc"))
	{
		fd = here_doc("EOF");
		debug_content_fd(fd, prompt, 1);
	}
	else if (command_ends_with(prompt, '|'))
	{
		fd = ends_in_pipe();
		debug_content_fd(fd, prompt, 2);
	}
}

void	miniprompt(t_minishell *minishell)
{
	char	*prompt;

	while (1)
	{
		handle_signal(SIGINT, prompt_signal_handler);
		handle_signal(SIGQUIT, SIG_IGN);
		prompt = readline(PROMPT_STRING);
		if (!prompt)
			break ;
		add_history(prompt);
		minishell->token_list = NULL;
		lexer(prompt, &minishell->token_list, STATE_SKIP);
		free(prompt);
		prompt = NULL;
		parser(minishell);
		executor(minishell);
		free_minishell(minishell);
	}
	write(STDOUT, "exit\n", 5);
	free(prompt);
}
