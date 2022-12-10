/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigpipe_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:29:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/10 11:31:30 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	handle_sigpipe(void)
{
	if (TRAP_SIGPIPE)
		handle_signal(SIGPIPE, SIG_DFL);
	else
		handle_signal(SIGPIPE, SIG_IGN);
}
