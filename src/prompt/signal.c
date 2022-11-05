/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:48:07 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/04 18:37:27 by eandre-f         ###   ########.fr       */
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
	if (sig == SIGINT)
	{
		write(STDERR, "\n", 1);
	}
	if (sig == SIGQUIT)
	{
		write(STDERR, "\n", 1);
	}
}