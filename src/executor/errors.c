/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:36:34 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/18 15:05:59 by eandre-f         ###   ########.fr       */
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
	if (error_number == ERR_IS_DIR)
		return (error_message(126, (char *[]){path, "Is a directory", 0}));
	else if (error_number == ERR_NOT_FOUND)
		return (error_message(127, (char *[]){
				path, "No such file or directory", 0
			}));
	else if (error_number == ERR_ACCESS)
		return (error_message(126, (char *[]){path, "Permission denied", 0}));
	else if (error_number == ERR_TOO_LONG)
		return (error_message(126, (char *[]){path, "File name too long", 0}));
	else if (error_number == ERR_OTHER)
		return (error_message(126, (char *[]){path, "File error", 0}));
	return (1);
}
