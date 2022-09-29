/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/09/29 11:08:28 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	miniprompt(void)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("minishell>");
		if (!prompt || !ft_strncmp(NULL, "exit", 4))
			break ;
		free(prompt);
	}
	free(prompt);
}
