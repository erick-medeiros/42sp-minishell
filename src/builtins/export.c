/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:52:31 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/16 13:06:53 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "expander.h"
#include "minishell.h"

static void	error_invalid_id(char *id);
static void	error_cant_update_var(char *name);

int	builtin_export(int argc, char *argv[], t_vlst *vars)
{
	int		idx;
	char	*name;
	char	*val;

	if (argc == 1)
	{
		print_sorted_vars(vars, " declare - x ");
		return (OK);
	}
	idx = 1;
	while (idx < argc)
	{
		split_name_val(argv[idx], &name, &val);
		if (!is_valid_name(name))
			error_invalid_id(argv[idx]);
		else if (change_or_create_var(vars, name, val))
			error_cant_update_var(argv[idx]);
		free(name);
		free(val);
		idx++;
	}
	return (OK);
}

static void	error_invalid_id(char *id)
{
	write(STDERR, "minishell: export: `", 20);
	write(STDERR, id, ft_strlen(id));
	write(STDERR, "': not a valid identifier\n", 26);
}

static void	error_cant_update_var(char *name)
{
	write(STDERR, "minishell: export: Error creating environment variable `",
		56);
	write(STDERR, name, ft_strlen(name));
	write(STDERR, "'\n", 2);
}
