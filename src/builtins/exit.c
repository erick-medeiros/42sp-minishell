/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:54:16 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/23 10:53:52 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "minishell.h"

static int	get_status(int argc, char *argv[], int last_status);
static void	clean_exit(t_exec *exec, t_vlst *env);

void	builtin_exit(t_exec *exec, int argc, char *argv[], t_vlst *env)
{
	int	status;

	status = get_status(argc, argv, env->last_status);
	clean_exit(exec, env);
	exit(status);
}

static int	get_status(int argc, char *argv[], int last_status)
{
	long long int	code;
	int				invalid;

	invalid = 0;
	if (argc > 1)
		code = ft_checked_atoll(argv[1], &invalid);
	if (invalid)
		return (error_message3(2, "exit", argv[1],
				"numeric argument required"));
	else if (argc > 2)
		return (error_message2(1, "exit", "too many arguments"));
	else if (argc == 2)
		return (code % 256LL);
	else
		return (last_status);
}

static void	clean_exit(t_exec *exec, t_vlst *env)
{
	if (env)
		clear_list(env->list, del_var_node);
	if (exec)
		destroy_exec(exec);
}
