/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:12:17 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/20 10:38:21 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(char *envp[])
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = NULL;
	while (envp != NULL && *envp != NULL && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!envp || !*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (paths != NULL)
	{
		i = 0;
		while (paths[i] != NULL)
		{
			tmp = paths[i];
			paths[i] = ft_strjoin(paths[i], "/");
			free(tmp);
			++i;
		}
	}
	return (paths);
}

char	*get_pathname(char *arg, char **path_list)
{
	char	*pathname;

	if (ft_strrchr(arg, '/'))
	{
		if (access(arg, F_OK | X_OK) == 0)
			return (ft_strdup(arg));
		return (NULL);
	}
	while (path_list && *path_list)
	{
		pathname = ft_strjoin(*path_list, arg);
		if (access(pathname, F_OK | X_OK) == 0)
			return (pathname);
		free(pathname);
		path_list++;
	}
	pathname = ft_strjoin("/usr/bin/", arg);
	if (access(pathname, F_OK | X_OK) == 0)
		return (ft_strdup(pathname));
	free(pathname);
	if (access(arg, F_OK | X_OK) == 0)
		return (ft_strdup(arg));
	return (NULL);
}
