/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:31 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/14 20:00:35 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*lexer(char *prompt)
{
	char	**cmd;
	// size_t	len;
	size_t	i;
	t_node *list;

	// len = ft_split_cmd_count(prompt, ' ');
	cmd = ft_split_cmd(prompt, ' ');
	list = NULL;
	i = 0;
	while (cmd[i])
	{
		add_node(&list, ft_strdup(cmd[i]));
		free(cmd[i]);
		++i;
	}
	free(cmd);
	return (list);
}
