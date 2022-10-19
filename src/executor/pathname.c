/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:12:17 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/19 19:24:03 by eandre-f         ###   ########.fr       */
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

char	*get_pathname(char *arg, char *envp[])
{
	char	*pathname;
	char	**paths;

	paths = get_paths(envp);
	if (ft_strrchr(arg, '/') != NULL)
	{
		if (access(arg, F_OK | X_OK) == 0)
			return (ft_strdup(arg));
		return (NULL);
	}
	while (paths != NULL && *paths != NULL)
	{
		pathname = ft_strjoin(*paths, arg);
		if (access(pathname, F_OK | X_OK) == 0)
			return (pathname);
		free(pathname);
		paths++;
	}
	pathname = ft_strjoin("/usr/bin/", arg);
	if (access(pathname, F_OK | X_OK) == 0)
		return (ft_strdup(pathname));
	free(pathname);
	if (access(arg, F_OK | X_OK) == 0)
		return (ft_strdup(arg));
	return (NULL);
}
