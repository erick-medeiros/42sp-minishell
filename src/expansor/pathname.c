/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:12:17 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/02 11:04:12 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansor.h"

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

static char	*check_path_env(char *arg, char *envp[])
{
	char	*pathname;
	char	**path_list;
	int		i;

	path_list = get_paths(envp);
	i = 0;
	while (path_list && path_list[i])
	{
		pathname = ft_strjoin(path_list[i], arg);
		if (access(pathname, F_OK | X_OK) == 0)
		{
			free_string_list(path_list);
			return (pathname);
		}
		free(pathname);
		++i;
	}
	free_string_list(path_list);
	return (NULL);
}

char	*get_pathname(char *arg, char *envp[])
{
	char	*pathname;

	if (ft_strrchr(arg, '/'))
	{
		if (access(arg, F_OK | X_OK) == 0)
			return (ft_strdup(arg));
		return (NULL);
	}
	pathname = check_path_env(arg, envp);
	if (pathname)
		return (pathname);
	pathname = ft_strjoin("/usr/bin/", arg);
	if (access(pathname, F_OK | X_OK) == 0)
		return (ft_strdup(pathname));
	free(pathname);
	if (access(arg, F_OK | X_OK) == 0)
		return (ft_strdup(arg));
	return (NULL);
}
