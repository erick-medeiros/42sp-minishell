/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:38:59 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/07 20:16:35 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_safe(int fd)
{
	if (fd > STDERR)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}

// string is equal

int	ft_streq(char *str1, char *str2)
{
	int	len;

	len = ft_max(ft_strlen(str1), ft_strlen(str2));
	if (ft_strncmp(str1, str2, len) == 0)
		return (TRUE);
	return (FALSE);
}

void	free_token(void *content)
{
	t_token	*token;
	int		*p_int;

	token = (t_token *)content;
	if (token->type == TOKEN_HEREDOC && token->value != NULL)
	{
		p_int = (int *)token->value;
		close(*p_int);
	}
	free(token->value);
	free(token);
}

void	free_string_list(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
