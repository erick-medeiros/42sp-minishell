/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:48:07 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 19:05:46 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig, void *handler)
{
	struct sigaction	act;

	act.sa_handler = handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	sigaction(sig, &act, NULL);
}

void	prompt_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR, "\n", 1);
		rl_replace_line("", TRUE);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	command_signal_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		write(STDERR, "\n", 1);
	}
}

void	incomplete_handler(int sig)
{
	(void)sig;
	write(STDERR, "\n", 1);
	rl_replace_line("", TRUE);
	rl_on_new_line();
	incomplete_signal_receiver(TRUE);
	rl_done = TRUE;
}

t_bool	*incomplete_signal_receiver(t_bool got_sigint)
{
	static t_bool	interrupted;

	interrupted = got_sigint;
	return (&interrupted);
}
