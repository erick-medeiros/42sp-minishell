/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:36:34 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/18 04:24:06 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>

void	print_signal_error(int exit_status)
{
	if (exit_status == 128 + SIGALRM)
		write(STDERR, "Alarm clock\n", 12);
	else if (exit_status == 128 + SIGHUP)
		write(STDERR, "Hangup\n", 7);
	else if (exit_status == 128 + SIGSEGV)
		write(STDERR, "Segmentation fault\n", 19);
	else if (exit_status == 128 + SIGTRAP)
		write(STDERR, "Trace/breakpoint trap\n", 22);
	else if (exit_status == 128 + SIGABRT)
		write(STDERR, "Aborted\n", 8);
	else if (exit_status == 128 + SIGFPE)
		write(STDERR, "Floating point exception\n", 25);
	else if (exit_status == 128 + SIGILL)
		write(STDERR, "Illegal instruction\n", 20);
	else if (exit_status == 128 + SIGKILL)
		write(STDERR, "Killed\n", 7);
	else if (exit_status == 128 + SIGQUIT)
		write(STDERR, "Quit\n", 5);
	else if (exit_status == 128 + SIGTERM)
		write(STDERR, "Terminated\n", 11);
}

int	print_file_error(char *path, int error_number)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (error_number == ERR_IS_DIR)
		ft_putstr_fd(": Is a directory\n", STDERR);
	else if (error_number == ERR_NOT_FOUND)
		ft_putstr_fd(": No such file or directory\n", STDERR);
	else if (error_number == ERR_ACCESS)
		ft_putstr_fd(": Permission denied\n", STDERR);
	else if (error_number == ERR_TOO_LONG)
		ft_putstr_fd(": File name too long\n", STDERR);
	else if (error_number == ERR_OTHER)
		ft_putstr_fd(": File error\n", STDERR);
	return (error_number);
}

int	set_exit_code(t_minishell *ms, int error_number)
{
	if (error_number == ERR_IS_DIR)
		ms->exit_status = 126;
	else if (error_number == ERR_NOT_FOUND)
		ms->exit_status = 127;
	else if (error_number == ERR_ACCESS)
		ms->exit_status = 126;
	else if (error_number == ERR_TOO_LONG)
		ms->exit_status = 126;
	else if (error_number == ERR_OTHER)
		ms->exit_status = 126;
	return (error_number);
}
