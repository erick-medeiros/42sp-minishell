/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/07 11:01:43 by eandre-f         ###   ########.fr       */
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

void	shell(t_minishell *minishell, char *line)
{
	minishell->token_list = NULL;
	lexer(line, &minishell->token_list, STATE_SKIP);
	free(line);
	parser(minishell);
	executor(minishell);
	free_minishell(minishell);
}

void	shell_loop(t_minishell *minishell)
{
	char	*line;

	while (1)
	{
		handle_signal(SIGINT, prompt_signal_handler);
		handle_signal(SIGQUIT, SIG_IGN);
		line = readline(get_prompt(minishell));
		if (!line)
		{
			write(STDOUT, "exit\n", 5);
			break ;
		}
		add_history(line);
		shell(minishell, line);
	}
}
