/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/04 18:07:46 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "libft.h"
#include "minishell.h"
#include "structs.h"

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

char	*get_prompt(t_minishell *minishell)
{
	static char	prompt[100];
	char		*custom;
	char		*status;
	char		*temp;

	status = ft_itoa(minishell->exit_status);
	temp = ft_strjoin(PROMPT_STRING, status);
	custom = ft_strjoin(temp, "> ");
	ft_strlcpy(prompt, custom, ft_strlen(custom));
	free(custom);
	free(status);
	free(temp);
	return (prompt);
}

void	miniprompt(t_minishell *minishell)
{
	char	*line;

	while (1)
	{
		handle_signal(SIGINT, prompt_signal_handler);
		handle_signal(SIGQUIT, SIG_IGN);
		line = readline(get_prompt(minishell));
		if (!line)
			break ;
		add_history(line);
		minishell->token_list = NULL;
		lexer(line, &minishell->token_list, STATE_SKIP);
		free(line);
		line = NULL;
		parser(minishell);
		executor(minishell);
		free_minishell(minishell);
	}
	write(STDOUT, "exit\n", 5);
	free(line);
}
