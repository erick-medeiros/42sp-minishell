/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:16:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 18:24:15 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "parser.h"

static int	read_heredoc_line(int fd, char *delim, t_vlst *env, char **line);

int	heredoc(char *delimiter, t_vlst *env, t_bool *interrupted)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
	{
		write(STDERR, "Error", 5);
		return (ERR_BAD_FD);
	}
	while (*interrupted == FALSE)
	{
		if (read_heredoc_line(pipefd[1], delimiter, env, &line))
			break ;
	}
	close(pipefd[1]);
	if (*interrupted == TRUE)
	{
		rl_done = FALSE;
		close(pipefd[0]);
		return (ERR_SIGINT);
	}
	free(line);
	return (pipefd[0]);
}

int	process_heredoc(t_token *token, char *delimiter, t_vlst *env)
{
	int		fd;
	int		*p_int;
	t_bool	*interrupted;

	interrupted = init_incomplete();
	fd = heredoc(delimiter, env, interrupted);
	handle_signal(SIGINT, prompt_signal_handler);
	if (fd < 0)
		return (fd);
	p_int = malloc(sizeof(int));
	if (p_int == NULL)
		return (ERR_ALLOC);
	*p_int = fd;
	token->value = (char *)p_int;
	return (OK);
}

static int	read_heredoc_line(int fd, char *delim, t_vlst *env, char **line)
{
	char	*expd;

	*line = readline(PROMPT_HEREDOC);
	if (!(*line) || ft_streq(*line, delim))
		return (1);
	expd = parameter_expansion(*line, env);
	write(fd, expd, ft_strlen(expd));
	write(fd, "\n", 1);
	free(expd);
	free(*line);
	return (0);
}

int	event(void)
{
	return (0);
}
