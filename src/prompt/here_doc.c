/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:16:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 08:51:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_here_doc(int pipefd[2], char *limiter);

int	here_doc(char	*limiter)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		write(STDERR, "Error", 5);
	pid = fork();
	if (pid < 0)
		write(STDERR, "Error", 5);
	if (pid == 0)
		child_here_doc(pipefd, limiter);
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	return (pipefd[0]);
}

static void	child_here_doc(int pipefd[2], char *limiter)
{
	char	*line;

	close(pipefd[0]);
	while (TRUE)
	{
		line = readline(HEREDOC_STRING);
		if (!line || ft_streq(line, limiter))
			break ;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	exit(0);
}
