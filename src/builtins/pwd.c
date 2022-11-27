/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:56 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/27 19:25:11 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

// pwd - print name of current/working directory

int	builtin_pwd(int fd_out)
{
	char	*retptr;

	retptr = getcwd(NULL, PATH_MAX);
	if (!retptr)
		return (error_message2(2, "pwd", strerror(errno)));
	ft_putendl_fd(retptr, fd_out);
	free(retptr);
	return (OK);
}
