/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:56 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/21 03:53:58 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "builtins_bonus.h"

// pwd - print name of current/working directory

int	builtin_pwd(int fd_out)
{
	char	*retptr;

	retptr = get_pwd();
	if (retptr == NULL)
		return (ERR_BUILTIN);
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
		ft_putstr_fd(MSG_PWD_ERR, STDERR);
		if (errno == ERANGE)
			ft_putstr_fd(MSG_PATH_MAX_ERR, STDERR);
		else if (errno == ENOMEM)
			ft_putstr_fd(MSG_PWD_ALLOC_ERR, STDERR);
		ft_putstr_fd("\n", STDERR);
		return (NULL);
	}
	return (retptr);
}
