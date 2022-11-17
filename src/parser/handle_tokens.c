/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 04:23:02 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/17 17:53:14 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_redir(t_tok_type redir_type, char *filename, t_cmd *cmd);

int	handle_word_token(t_tree *cmd_node, t_minishell *ms)
{
	t_cmd	*cmd;
	t_token	*tok;

	cmd = ((t_cmd *)cmd_node->content);
	tok = ms->token_list->content;
	add_node(&cmd->word_tokens, ft_strdup(tok->value));
	return (OK);
}

int	handle_redirect_token(t_tree *cmd_node, t_minishell *ms)
{
	int			result;
	t_cmd		*cmd;
	t_token		*tok;

	cmd = ((t_cmd *)cmd_node->content);
	tok = ((t_token *)ms->token_list->content);
	ms->token_list = remove_node(ms->token_list, del_token_node);
	if (ms->token_list == NULL)
		return (ERR_BAD_SYNTAX);
	if (((t_token *)ms->token_list->content)->type != TOKEN_WORD)
		return (ERR_BAD_SYNTAX);
	result = set_redir(tok->type, tok->value, cmd);
	if (result != OK)
		return (result);
	return (OK);
}

int	enqueue_heredoc(t_tree *cmd_node, t_minishell *ms)
{
	t_heredoc	*content;

	ms->token_list = remove_node(ms->token_list, del_token_node);
	if (ms->token_list == NULL)
		return (ERR_BAD_SYNTAX);
	if (((t_token *)ms->token_list->content)->type != TOKEN_WORD)
		return (ERR_BAD_SYNTAX);
	content = malloc(sizeof(*content));
	if (content == NULL)
		return (ERR_ALLOC);
	content->cmd = cmd_node->content;
	content->delimiter = ft_strdup(((t_token *)ms->token_list->content)->value);
	return (enqueue(&ms->heredoc_queue, content));
}

static int	set_redir(t_tok_type type, char *filename, t_cmd *cmd)
{
	t_token	*token;

	if (type == TOKEN_INPUT || type == TOKEN_OUTPUT || type == TOKEN_APPEND)
	{
		token = malloc(sizeof(t_token));
		token->value = ft_strdup(filename);
		token->type = type;
		add_node(&cmd->redirect, token);
	}
	return (OK);
}
