/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:36:34 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/17 23:52:56 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
