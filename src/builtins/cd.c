/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:53:49 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/02 10:42:55 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "expander.h"

//cd — change the working directory

static char	*get_home(t_vlst *vars);
static void	sets_env_vars(t_vlst *vars, char *wdir);

int	builtin_cd(int argc, char *argv[], t_vlst *vars)
{
	char	*wdir;
	char	*path;

	if (argc > 2)
		return (error_message2(1, "cd", "too many arguments"));
	else if (argc == 2)
		path = argv[1];
	else
	{
		path = get_home(vars);
		if (!path)
			return (error_message2(1, "cd", "HOME not set"));
	}
	if (chdir(path) == -1)
		return (error_message3(1, "cd", path, strerror(errno)));
	wdir = getcwd(NULL, 0);
	if (!wdir)
		return (error_message2(1, "cd", strerror(errno)));
	if (vars)
		sets_env_vars(vars, wdir);
	free(wdir);
	return (OK);
}

static char	*get_home(t_vlst *vars)
{
	t_node	*node;

	node = find_node_by_content(vars->list, "HOME", find_env_var);
	if (node)
		return (((t_var *)node->content)->val);
	return (NULL);
}

static void	sets_env_vars(t_vlst *vars, char *wdir)
{
	t_node	*node;

	node = find_node_by_content(vars->list, "PWD", find_env_var);
	if (node)
		update_var(vars, new_var_node_from_name_val("OLDPWD",
				((t_var *)node->content)->val));
	update_var(vars, new_var_node_from_name_val("PWD", wdir));
}
