/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 04:23:02 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/07 10:07:39 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	save_redirect(t_node **lst, t_tok_type rd_type,
				char *filename, t_ms *ms);

int	handle_word_token(t_tree *cmd_node, t_ms *ms)
{
	t_cmd	*cmd;
	t_token	*tok;
	t_token	*add;

	cmd = ((t_cmd *)cmd_node->content);
	tok = ms->token_list->content;
	add = malloc(sizeof(t_token));
	add->value = ft_strdup(tok->value);
	add->type = TOKEN_WORD;
	add_node(&cmd->word_tokens, add);
	return (OK);
}

int	handle_redirect_token(t_tree *cmd_node, t_ms *ms)
{
	char		*filename;
	t_cmd		*cmd;
	t_tok_type	rd_type;
	t_tok_type	next_type;
	int			result;

	result = OK;
	cmd = ((t_cmd *)cmd_node->content);
	rd_type = ((t_token *)ms->token_list->content)->type;
	ms->token_list = remove_node(ms->token_list, del_token_node);
	if (ms->token_list == NULL)
		return (print_token_error(ERR_BAD_SYNTAX, NULL));
	next_type = ((t_token *)ms->token_list->content)->type;
	if (next_type != TOKEN_WORD)
		return (print_token_error(ERR_BAD_SYNTAX, ms->token_list->content));
	filename = ((t_token *)ms->token_list->content)->value;
	result = save_redirect(&cmd->redirect, rd_type, filename, ms);
	return (result);
}

static int	save_redirect(t_node **lst, t_tok_type rd_type,
				char *filename, t_ms *ms)
{
	t_token	*token;
	int		result;

	token = malloc(sizeof(t_token));
	token->type = rd_type;
	if (rd_type == TOKEN_HEREDOC)
	{
		ms->set_history = FALSE;
		result = process_heredoc(token, filename, &ms->env_list);
		if (result != OK)
		{
			free(token);
			return (result);
		}
	}
	else
		token->value = ft_strdup(filename);
	if (add_node(lst, token) != OK)
	{
		free(token);
		return (ERR_ALLOC);
	}
	return (OK);
}

int	handle_next_token(t_tree *cmd_node, t_ms *ms)
{
	t_token		*tok;

	tok = ((t_token *)(ms->token_list->content));
	if (tok->type == TOKEN_WORD)
		return (handle_word_token(cmd_node, ms));
	if (tok->type == TOKEN_INPUT || tok->type == TOKEN_OUTPUT
		|| tok->type == TOKEN_APPEND || tok->type == TOKEN_HEREDOC)
		return (handle_redirect_token(cmd_node, ms));
	return (handle_next_token_error(ms));
}
