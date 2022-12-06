/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:52:31 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/06 19:32:47 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"
#include "minishell.h"

static int	error_invalid_id(char *id);
static int	error_cant_update_var(char *name);

int	builtin_export(int argc, char *argv[], t_vlst *vars)
{
	int		idx;
	int		result;
	char	*name;
	char	*val;

	result = 0;
	if (argc == 1)
	{
		print_sorted_vars(vars, "declare -x ");
		return (OK);
	}
	idx = 1;
	while (idx < argc)
	{
		split_name_val(argv[idx], &name, &val);
		if (!is_valid_name(name))
			result = error_invalid_id(argv[idx]);
		else if (change_or_create_var(vars, name, val))
			result = error_cant_update_var(argv[idx]);
		free(name);
		free(val);
		idx++;
	}
	return (result);
}

static int	error_invalid_id(char *id)
{
	write(STDERR, "minishell: export: `", 20);
	write(STDERR, id, ft_strlen(id));
	write(STDERR, "': not a valid identifier\n", 26);
	return (1);
}

static int	error_cant_update_var(char *name)
{
	write(STDERR, "minishell: export: Error creating environment variable `",
		56);
	write(STDERR, name, ft_strlen(name));
	write(STDERR, "'\n", 2);
	return (1);
}
