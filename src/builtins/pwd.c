/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:56 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/13 14:38:58 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("Error: get working directory failed\n");
		if (errno == ERANGE)
			printf("Error: path max buffer\n");
		else if (errno == ENOMEM)
			printf("Error: memory cannot be allocated\n");
		return (NULL);
	}
	return (retptr);
}
