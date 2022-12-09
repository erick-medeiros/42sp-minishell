/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:54:16 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/09 12:01:05 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "minishell.h"

static int	get_status(int argc, char *argv[], int last_status);
static void	clean_exit(t_exec *exec);

void	builtin_exit(t_exec *exec, int status)
{
	clean_exit(exec);
	exit(status);
}

void	builtin_exit_arg(t_exec *exec, int argc, char *argv[])
{
	int	status;

	if (isatty(STDIN) != 0)
		write(STDERR, "exit\n", 5);
	status = exec->env->last_status;
	if (argc > 1)
		status = get_status(argc, argv, status);
	builtin_exit(exec, status);
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

static void	clean_exit(t_exec *exec)
{
	if (exec)
	{
		if (exec->env)
			clear_list(exec->env->list, del_var_node);
		destroy_exec(exec);
	}
	rl_clear_history();
}
