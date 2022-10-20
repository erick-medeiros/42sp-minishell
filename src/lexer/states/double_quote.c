/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 03:20:40 by gmachado          #+#    #+#             */
/*   Updated: 2022/10/20 03:36:40 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex_state	handle_dquote_state(char next_ch, t_node **tokens)
{
	(void)tokens;
	if (next_ch == '|')
		return (STATE_PIPE);
	else if (next_ch == '>')
		return (STATE_OUTPUT);
	else if (next_ch == '<')
		return (STATE_INPUT);
	else if (next_ch == '"')
		return (STATE_DQUOTE);
	else if (next_ch == '\'')
		return (STATE_SQUOTE);
	else if (ft_isspace(next_ch))
		return (STATE_SPACE);
	else if (next_ch == '\0')
		return (STATE_COMPLETE);
	else
		return (STATE_WORD);
}
