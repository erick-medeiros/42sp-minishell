/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 02:11:33 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/06 15:20:12 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	new_token(t_node **tokens, t_tok_type tok_type)
{
	t_token	*content;

	content = malloc(sizeof(*content));
	if (!content)
		return (ERR_ALLOC);
	content->type = tok_type;
	content->value = NULL;
	return (add_node(tokens, content));
}

int	new_token_filled(t_node **tokens, t_tok_type type, char *value)
{
	t_token	*content;

	content = malloc(sizeof(*content));
	if (!content)
		return (ERR_ALLOC);
	content->type = type;
	content->value = value;
	return (add_node(tokens, content));
}

int	new_token_with_val(t_node **tokens, t_tok_type tok_type, t_val_info *vi)
{
	t_token	*content;
	char	*val;

	content = malloc(sizeof(*content));
	if (!content)
		return (ERR_ALLOC);
	val = malloc(sizeof(*val) * (vi->len + 1));
	if (!val)
	{
		free(content);
		return (ERR_ALLOC);
	}
	content->type = tok_type;
	ft_strlcpy(val, vi->line + vi->start, vi->len + 1);
	content->value = val;
	vi->len = 0;
	return (add_node(tokens, content));
}

t_lex_state	init_word_value(size_t idx, t_val_info *vi, t_lex_state st)
{
	vi->start = idx;
	vi->len = 1;
	return (st);
}

t_lex_state	new_word_token(t_node **tokens,
	t_val_info *vi, t_lex_state next_state)
{
	if (new_token_with_val(tokens, TOKEN_WORD, vi))
		return (STATE_INVALID);
	return (next_state);
}
