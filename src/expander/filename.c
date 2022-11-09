/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:32:33 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/09 16:12:24 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	pattern_matching(char *match, struct dirent *direntp)
{
	(void)match;
	if (ft_strcmp(".", direntp->d_name) == 0)
		return (FALSE);
	if (ft_strcmp("..", direntp->d_name) == 0)
		return (FALSE);
	return (TRUE);
}

t_node	*directory_files(char *match)
{
	struct dirent	*direntp;
	DIR				*dirp;
	t_node			*list;

	list = NULL;
	dirp = opendir(".");
	if (dirp == NULL)
		panic_error("Cannot open directory");
	while (1)
	{
		errno = 0;
		direntp = readdir(dirp);
		if (!direntp)
		{
			if (errno != 0)
				panic_error(strerror(errno));
			break ;
		}
		if (pattern_matching(match, direntp))
			add_node(&list, direntp->d_name);
	}
	closedir(dirp);
	return (list);
}

char	*filename_expander(char *match)
{
	t_node	*list;

	if (!match)
		return (match);
	list = directory_files(match);
	while (list)
	{
		printf("%s", ((char *)list->content));
		list = list->next;
		if (list)
			printf(" ");
	}
	printf("\n\n");
	clear_list(list, free);
	return (NULL);
}
