/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:49 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/27 19:24:30 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "expander.h"
#include "structs.h"

//cd — change the working directory
static int	cd_error(char *path);

int	builtin_cd(int argc, char *argv[], t_vlst *vars)
{
	char	*retptr;
	char	*path;
	t_node	*node;

	if (argc != 2)
		return (error_message1(1, "too many arguments"));
	path = argv[1];
	if (chdir(path) == -1)
		return (cd_error(path));
	retptr = getcwd(NULL, PATH_MAX);
	if (!retptr)
		error_message2(2, "cd", strerror(errno));
	if (retptr)
	{
		if (vars)
		{
			node = find_node_by_content(vars->list, "PWD", find_env_var);
			if (node)
				update_var(vars, new_var_node_from_name_val("OLDPWD",
						((t_var *)node->content)->val));
			update_var(vars, new_var_node_from_name_val("PWD", retptr));
		}
		free(retptr);
	}
	return (OK);
}

static int	cd_error(char *path)
{
	const char	*access_err[] = {"cd", path, "Permission denied", NULL};
	const char	*loop_err[] = {"cd", path, "Loop in directory", NULL};
	const char	*too_long_err[] = {"cd", path, "File name too long", NULL};
	const char	*n_fnd_err[] = {"cd", path, "No such file or directory", NULL};
	const char	*not_dir_err[] = {"cd", path, "Not a directory", NULL};

	if (errno == EACCES)
		return (error_message(1, (char **)access_err));
	if (errno == ELOOP)
		return (error_message(1, (char **)loop_err));
	if (errno == ENAMETOOLONG)
		return (error_message(1, (char **)too_long_err));
	if (errno == ENOENT)
		return (error_message(1, (char **)n_fnd_err));
	if (errno == ENOTDIR)
		return (error_message(1, (char **)not_dir_err));
	return (2);
}
