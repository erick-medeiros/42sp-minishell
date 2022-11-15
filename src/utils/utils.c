/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:38:59 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 08:50:04 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// string is equal

int	ft_streq(char *str1, char *str2)
{
	int	len;

	len = ft_max(ft_strlen(str1), ft_strlen(str2));
	if (ft_strncmp(str1, str2, len) == 0)
		return (TRUE);
	return (FALSE);
}

int	command_ends_with(char *cmd, char c)
{
	int	index;

	if (cmd == NULL)
		return (FALSE);
	index = ft_strlen(cmd) - 1;
	if (index < 0)
		return (FALSE);
	if (cmd[index] == c)
		return (TRUE);
	return (FALSE);
}

char	*get_content_fd(int fd)
{
	char	buffer[101];
	int		i;
	int		bytes;
	char	*tmp;
	char	*content;

	i = -1;
	while (++i < 101)
		buffer[i] = '\0';
	content = ft_strdup("");
	while (TRUE)
	{
		bytes = read(fd, buffer, 100);
		buffer[bytes] = '\0';
		buffer[bytes] = '\0';
		if (bytes <= 0)
			break ;
		tmp = content;
		content = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	return (content);
}
