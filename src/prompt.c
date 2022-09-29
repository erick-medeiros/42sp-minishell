/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/09/29 10:19:57 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	miniprompt(void)
{
	char	*prompt;

	prompt = readline("minishell>");
	while (prompt)
	{
		free(prompt);
		prompt = readline("minishell>");
	}
}
