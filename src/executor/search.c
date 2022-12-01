/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:51:23 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/01 18:07:40 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

static int	defined_path(t_cmd *command);
static int	command_is_builtin(t_cmd *command);
static int	search_in_directories(t_cmd *command, t_vlst *env);
static int	check_runnable(char *path);

int	command_search(t_cmd *command, t_vlst *env)
{
	int	result;

	if (command->argc == 0)
		return (0);
	result = defined_path(command);
	if (result == OK)
		return (OK);
	if (command_is_builtin(command) == OK)
		return (OK);
	if (result == ERR_NO_PATH)
		result = search_in_directories(command, env);
	return (result);
}

static int	defined_path(t_cmd *command)
{
	int	result;

	command->pathname = NULL;
	if (ft_strrchr(command->argv[0], '/'))
	{
		result = check_runnable(command->argv[0]);
		if (result == OK)
			command->pathname = ft_strdup(command->argv[0]);
		return (result);
	}
	return (ERR_NO_PATH);
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
	if (ft_streq(command->argv[0], "true")
		|| ft_streq(command->argv[0], "false"))
	{
		command->isbuiltin = TRUE;
		return (OK);
	}
	return (ERR_NOT_FOUND);
}

static int	search_in_directories(t_cmd *command, t_vlst *env)
{
	char	*env_path;
	char	**path_list;
	char	*path;
	int		i;

	env_path = expand_variable("$PATH", env);
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
			return (check_runnable(command->pathname));
		}
		free(command->pathname);
		++i;
	}
	free_string_list(path_list);
	command->pathname = NULL;
	return (ERR_CMD_NOT_FOUND);
}

static int	check_runnable(char *path)
{
	struct stat	buf;

	if (stat(path, &buf))
	{
		if (errno == ENOENT || errno == ENOTDIR)
			return (print_file_error(path, ERR_NOT_FOUND));
		if (errno == ENAMETOOLONG)
			return (print_file_error(path, ERR_TOO_LONG));
		if (errno == EACCES)
			return (print_file_error(path, ERR_ACCESS));
		return (print_file_error(path, ERR_OTHER));
	}
	if (S_ISDIR(buf.st_mode))
		return (print_file_error(path, ERR_IS_DIR));
	if (access(path, X_OK))
		return (print_file_error(path, ERR_ACCESS));
	return (OK);
}
