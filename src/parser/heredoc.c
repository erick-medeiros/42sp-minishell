/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:16:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/02 16:34:26 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"

int	heredoc(char *delimiter, t_vlst *env)
{
	int		pipefd[2];
	char	*line;
	char	*expd;

	if (pipe(pipefd) < 0)
	{
		write(STDERR, "Error", 5);
		return (-1);
	}
	while (TRUE)
	{
		line = readline(HEREDOC_STRING);
		if (!line || ft_streq(line, delimiter))
			break ;
		expd = parameter_expansion(line, env);
		write(pipefd[1], expd, ft_strlen(expd));
		write(pipefd[1], "\n", 1);
		free(expd);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	process_heredoc(t_token *token, char *delimiter, t_vlst *env)
{
	int	fd;
	int	*p_int;

	fd = heredoc(delimiter, env);
	if (fd < 0)
		return (ERR_BAD_SUBST);
	p_int = malloc(sizeof(int));
	if (p_int == NULL)
		return (ERR_ALLOC);
	*p_int = fd;
	token->value = (char *)p_int;
	return (OK);
}
