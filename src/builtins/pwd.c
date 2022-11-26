/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:56 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/26 14:11:55 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

// pwd - print name of current/working directory

int	builtin_pwd(int fd_out)
{
	char	*retptr;

	retptr = get_pwd();
	if (retptr == NULL)
		return (2);
	ft_putendl_fd(retptr, fd_out);
	free(retptr);
	return (OK);
}

char	*get_pwd(void)
{
	char	*retptr;

	retptr = getcwd(NULL, 1024);
	if (retptr == NULL)
	{
		ft_putendl_fd("Error: get working directory failed", STDERR);
		if (errno == ERANGE)
			ft_putendl_fd("Error: path max buffer", STDERR);
		else if (errno == ENOMEM)
			ft_putendl_fd("Error: memory cannot be allocated", STDERR);
		return (NULL);
	}
	return (retptr);
}
