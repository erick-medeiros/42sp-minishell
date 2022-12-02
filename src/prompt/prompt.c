/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/02 11:42:55 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_prompt(t_vlst *env)
{
	static char	prompt[100];
	char		*custom;
	char		*status;
	char		*temp;

	status = ft_itoa(env->last_status);
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
		handle_signal(SIGPIPE, SIG_IGN);
		minishell->set_history = TRUE;
		line = readline(get_prompt(&minishell->env_list));
		if (!line)
		{
			write(STDOUT, "exit\n", 5);
			break ;
		}
		process_line(&line, minishell);
		free_minishell(minishell);
	}
}
