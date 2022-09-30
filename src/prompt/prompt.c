/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/09/30 13:35:08 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_is_equal(char *cmd, char *str)
{
	int	len;

	len = ft_max(ft_strlen(cmd), ft_strlen(str));
	if (ft_strncmp(cmd, str, len) == 0)
		return (TRUE);
	return (FALSE);
}

// read fd returned in here_doc
void	temp_function(int fd)
{
	char	buff[100];
	int		i;

	i = -1;
	while (++i < 100)
		buff[i] = '\0';
	read(fd, buff, 100);
	write(STDOUT, buff, 100);
	write(STDOUT, "\n", 1);
}

void	miniprompt(void)
{
	char	*prompt;
	int		fd;

	while (1)
	{
		prompt = readline(PROMPT_TEXT);
		if (!prompt || command_is_equal(prompt, "exit"))
			break ;
		if (command_is_equal(prompt, "here_doc"))
		{
			fd = here_doc("EOF");
			temp_function(fd);
			close(fd);
		}
		free(prompt);
	}
	free(prompt);
}
