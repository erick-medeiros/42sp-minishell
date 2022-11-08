/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:41:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/08 17:46:46 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SINGLE_QUOTE 39
#define DOUBLE_QUOTE 34

static int	isquote(char c)
{
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
		return (TRUE);
	return (FALSE);
}

static int	update_quote(char c, int quote)
{
	if (c == SINGLE_QUOTE && !quote)
		quote = SINGLE_QUOTE;
	else if (c == DOUBLE_QUOTE && !quote)
		quote = DOUBLE_QUOTE;
	else if (isquote(c) && quote == c)
		quote = 0;
	return (quote);
}

char	*clean_quote_expansor(char *str)
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
		if (isquote(str[i]) && (!quote || str[i] == quote))
			quote = update_quote(str[i], quote);
		else
			new[j++] = str[i];
		++i;
	}
	free(str);
	new[j] = '\0';
	return (new);
}
