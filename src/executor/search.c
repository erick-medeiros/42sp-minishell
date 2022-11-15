/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:51:23 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 14:21:37 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

static int	defined_path(t_cmd *command)
{
	command->pathname = NULL;
	if (ft_strrchr(command->argv[0], '/'))
	{
		if (access(command->argv[0], F_OK) == 0)
		{
			command->pathname = ft_strdup(command->argv[0]);
			return (OK);
		}
	}
	return (ERR_NOT_FOUND);
}

static int	command_is_builtin(t_cmd *command)
{
	command->pathname = NULL;
	command->isbuiltin = FALSE;
	if (ft_streq(command->argv[0], "echo")
		|| ft_streq(command->argv[0], "cd")
		|| ft_streq(command->argv[0], "pwd")
		|| ft_streq(command->argv[0], "export")
		|| ft_streq(command->argv[0], "unset")
		|| ft_streq(command->argv[0], "env")
		|| ft_streq(command->argv[0], "exit"))
	{
		command->isbuiltin = TRUE;
		return (OK);
	}
	return (ERR_NOT_FOUND);
}

static int	search_in_directories(t_cmd *command, t_vlst *env_list)
{
	char	*env_path;
	char	**path_list;
	char	*path;
	int		i;

	env_path = expand_variable(env_list, "$PATH");
	path_list = ft_split(env_path, ':');
	free(env_path);
	i = 0;
	while (path_list && path_list[i])
	{
		path = ft_strjoin(path_list[i], "/");
		command->pathname = ft_strjoin(path, command->argv[0]);
		free(path);
		if (access(command->pathname, F_OK) == 0)
		{
			free_string_list(path_list);
			return (OK);
		}
		free(command->pathname);
		++i;
	}
	free_string_list(path_list);
	command->pathname = NULL;
	return (ERR_NOT_FOUND);
}

int	command_search(t_cmd *command, t_vlst *env_list)
{
	if (defined_path(command) == OK)
		return (OK);
	if (command_is_builtin(command) == OK)
		return (OK);
	if (search_in_directories(command, env_list) == OK)
		return (OK);
	return (ERR_NOT_FOUND);
}
