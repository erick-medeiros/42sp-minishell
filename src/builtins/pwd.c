/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:56 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/13 01:28:08 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

// pwd - print name of current/working directory

void	builtin_pwd(void)
{
	char	*retptr;

	retptr = get_pwd();
	if (retptr == NULL)
		return ;
	write(STDOUT, retptr, ft_strlen(retptr));
	write(STDOUT, "\n", 1);
	free(retptr);
}

char	*get_pwd(void)
{
	char	*retptr;

	retptr = getcwd(NULL, 1024);
	if (retptr == NULL)
	{
		write(STDERR, MSG_PWD_ERR, ft_strlen(MSG_PWD_ERR));
		write(STDERR, "\n", 1);
		if (errno == ERANGE)
			write(STDERR, MSG_PATH_MAX_ERR, ft_strlen(MSG_PATH_MAX_ERR));
		else if (errno == ENOMEM)
			write(STDERR, MSG_PWD_ALLOC_ERR, ft_strlen(MSG_PWD_ALLOC_ERR));
		write(STDERR, "\n", 1);
		return (NULL);
	}
	return (retptr);
}
