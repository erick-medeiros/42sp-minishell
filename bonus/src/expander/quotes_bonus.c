/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:41:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/21 03:57:43 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "expander_bonus.h"

int	update_quote(char c, int quote)
{
	if (c == SINGLE_QUOTE && !quote)
		quote = SINGLE_QUOTE;
	else if (c == DOUBLE_QUOTE && !quote)
		quote = DOUBLE_QUOTE;
	else if (ft_isquote(c) && quote == c)
		quote = 0;
	return (quote);
}

char	*remove_quote(char *str)
{
	char	*new;
	int		quote;
	int		i;
	int		j;

	if (!str)
		return (str);
	quote = 0;
	new = ft_strdup(str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) && (!quote || str[i] == quote))
			quote = update_quote(str[i], quote);
		else
			new[j++] = str[i];
		++i;
	}
	new[j] = '\0';
	return (new);
}
