/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:09:49 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 19:12:05 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

#define BUFFER_SIZE 1000
#define FD_LIMIT 1024

static char	*get_line(char **acc)
{
	size_t	c;
	char	*s;
	char	*r;

	if (*acc == NULL)
		return (NULL);
	c = (size_t)(ft_strchr(*acc, '\n') - *acc) + 1;
	s = ft_substr(*acc, 0, c);
	r = ft_substr(*acc, c, ft_strlen(*acc));
	free(*acc);
	*acc = NULL;
	if (r && r[0] == '\0')
		free(r);
	else
		*acc = r;
	return (s);
}

static void	read_line(int fd, char **acc, char *buffer)
{
	int		read_bytes;
	char	*tmp;

	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1 || read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		if (*acc == NULL)
			*acc = ft_strdup("");
		tmp = *acc;
		*acc = ft_strjoin(*acc, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n') != NULL)
			break ;
	}
}

char	*get_next_line(int fd)
{
	static char	*acc[FD_LIMIT];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	read_line(fd, &acc[fd], buffer);
	line = get_line(&acc[fd]);
	free(buffer);
	return (line);
}
