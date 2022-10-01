/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ends_in_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:11:33 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/01 12:48:25 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_ends_in_pipe(int pipefd[2]);

int	ends_in_pipe(void)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		write(STDERR, "Error", 5);
	pid = fork();
	if (pid < 0)
		write(STDERR, "Error", 5);
	if (pid == 0)
		child_ends_in_pipe(pipefd);
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	return (pipefd[0]);
}

static void	child_ends_in_pipe(int pipefd[2])
{
	char	*line;

	close(pipefd[0]);
	while (TRUE)
	{
		line = readline(ENDSINPIPE_STRING);
		if (!line)
			break ;
		write(pipefd[1], line, ft_strlen(line));
		if (!command_ends_with(line, '|'))
			break ;
		free(line);
	}
	free(line);
	close(pipefd[1]);
	exit(0);
}
