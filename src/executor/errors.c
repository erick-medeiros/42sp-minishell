/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:36:34 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/18 13:54:25 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>

static void	print_signal_error_msg(char *msg, int coredump);

void	print_signal_error(int exit_status, int coredump)
{
	char	*msg;

	msg = NULL;
	if (exit_status == 128 + SIGALRM)
		msg = "Alarm clock";
	else if (exit_status == 128 + SIGHUP)
		msg = "Hangup";
	else if (exit_status == 128 + SIGSEGV)
		msg = "Segmentation fault";
	else if (exit_status == 128 + SIGTRAP)
		msg = "Trace/breakpoint trap";
	else if (exit_status == 128 + SIGABRT)
		msg = "Aborted";
	else if (exit_status == 128 + SIGFPE)
		msg = "Floating point exception";
	else if (exit_status == 128 + SIGILL)
		msg = "Illegal instruction";
	else if (exit_status == 128 + SIGKILL)
		msg = "Killed";
	else if (exit_status == 128 + SIGQUIT)
		msg = "Quit";
	else if (exit_status == 128 + SIGTERM)
		msg = "Terminated";
	print_signal_error_msg(msg, coredump);
}

static void	print_signal_error_msg(char *msg, int coredump)
{
	const short	buffer_size = 37;
	const short	coredump_size = 13;
	int			len_msg;
	int			i;

	if (!msg)
		return ;
	if (!coredump)
	{
		ft_putendl_fd(msg, STDERR);
		return ;
	}
	len_msg = ft_strlen(msg);
	ft_putstr_fd(msg, STDERR);
	i = -1;
	while (++i < (int)(buffer_size - coredump_size - len_msg))
		ft_putstr_fd(" ", STDERR);
	ft_putstr_fd("(core dumped)\n", STDERR);
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
