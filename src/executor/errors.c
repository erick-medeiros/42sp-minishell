/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:36:34 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/06 19:31:27 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_signal_error_msg(char *msg, int coredump);

void	print_signal_error(int exit_status, int coredump)
{
	if (exit_status == 128 + SIGALRM)
		print_signal_error_msg("Alarm clock", coredump);
	else if (exit_status == 128 + SIGHUP)
		print_signal_error_msg("Hangup", coredump);
	else if (exit_status == 128 + SIGSEGV)
		print_signal_error_msg("Segmentation fault", coredump);
	else if (exit_status == 128 + SIGTRAP)
		print_signal_error_msg("Trace/breakpoint trap", coredump);
	else if (exit_status == 128 + SIGABRT)
		print_signal_error_msg("Aborted", coredump);
	else if (exit_status == 128 + SIGFPE)
		print_signal_error_msg("Floating point exception", coredump);
	else if (exit_status == 128 + SIGILL)
		print_signal_error_msg("Illegal instruction", coredump);
	else if (exit_status == 128 + SIGKILL)
		print_signal_error_msg("Killed", coredump);
	else if (exit_status == 128 + SIGQUIT)
		print_signal_error_msg("Quit", coredump);
	else if (exit_status == 128 + SIGTERM)
		print_signal_error_msg("Terminated", coredump);
	else if (exit_status == 128 + SIGINT)
		print_signal_error_msg("", coredump);
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
	if (error_number == ERR_IS_DIR)
		return (error_message2(126, path, "Is a directory"));
	else if (error_number == ERR_NOT_FOUND)
		return (error_message2(127, path, "No such file or directory"));
	else if (error_number == ERR_ACCESS)
		return (error_message2(126, path, "Permission denied"));
	else if (error_number == ERR_TOO_LONG)
		return (error_message2(126, path, "File name too long"));
	else if (error_number == ERR_OTHER)
		return (error_message2(126, path, "File error"));
	return (1);
}

int	command_not_found_handle(char *name)
{
	ft_putstr_fd(name, STDERR);
	ft_putendl_fd(": command not found", STDERR);
	return (127);
}
