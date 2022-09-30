/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/09/29 16:46:00 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	miniprompt(void)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("minishell>");
		if (!prompt || !ft_strncmp(prompt, "exit", 4))
			break ;
		free(prompt);
	}
	free(prompt);
}
