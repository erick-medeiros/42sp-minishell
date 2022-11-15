/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 01:08:28 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"

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

void	shell(t_minishell *minishell, char **line)
{
	minishell->set_history = FALSE;
	process_line(line, minishell);
	free_minishell(minishell);
}

void	shell_loop(t_minishell *minishell)
{
	char	*line;

	while (1)
	{
		handle_signal(SIGINT, prompt_signal_handler);
		handle_signal(SIGQUIT, SIG_IGN);
		minishell->set_history = TRUE;
		line = readline(get_prompt(minishell));
		if (!line)
		{
			write(STDOUT, "exit\n", 5);
			break ;
		}
		process_line(&line, minishell);
		free_minishell(minishell);
	}
}
