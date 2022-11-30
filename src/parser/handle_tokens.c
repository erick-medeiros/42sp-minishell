/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 04:23:02 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/29 19:26:53 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	handle_word_token(t_tree *cmd_node, t_minishell *ms)
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

int	handle_redirect_token(t_tree *cmd_node, t_minishell *ms)
{
	char		*filename;
	t_cmd		*cmd;
	t_tok_type	redir_type;
	t_tok_type	next_type;
	t_token		*token;

	cmd = ((t_cmd *)cmd_node->content);
	redir_type = ((t_token *)ms->token_list->content)->type;
	ms->token_list = remove_node(ms->token_list, del_token_node);
	if (ms->token_list == NULL)
		return (print_token_error(ERR_BAD_SYNTAX, NULL));
	next_type = ((t_token *)ms->token_list->content)->type;
	if (next_type != TOKEN_WORD)
		return (print_token_error(ERR_BAD_SYNTAX, ms->token_list->content));
	filename = ((t_token *)ms->token_list->content)->value;
	if (is_redir_token(redir_type))
	{
		token = malloc(sizeof(t_token));
		token->value = ft_strdup(filename);
		token->type = redir_type;
		add_node(&cmd->redirect, token);
	}
	return (OK);
}

int	enqueue_heredoc(t_tree *cmd_node, t_minishell *ms)
{
	t_heredoc	*content;
	t_tok_type	next_type;

	ms->token_list = remove_node(ms->token_list, del_token_node);
	if (ms->token_list == NULL)
		return (print_token_error(ERR_BAD_SYNTAX, NULL));
	next_type = ((t_token *)ms->token_list->content)->type;
	if (next_type != TOKEN_WORD)
		return (print_token_error(ERR_BAD_SYNTAX, ms->token_list->content));
	content = malloc(sizeof(*content));
	if (content == NULL)
		return (ERR_ALLOC);
	content->cmd = cmd_node->content;
	content->delimiter = ft_strdup(((t_token *)ms->token_list->content)->value);
	return (enqueue(&ms->heredoc_queue, content));
}

int	handle_group_redirect_token(t_tree *group_node, t_minishell *ms)
{
	char		*filename;
	t_tok_type	redir_type;
	t_tok_type	next_type;
	t_token		*token;

	redir_type = ((t_token *)ms->token_list->content)->type;
	ms->token_list = remove_node(ms->token_list, del_token_node);
	if (ms->token_list == NULL)
		return (print_token_error(ERR_BAD_SYNTAX, NULL));
	next_type = ((t_token *)ms->token_list->content)->type;
	if (next_type != TOKEN_WORD)
		return (print_token_error(ERR_BAD_SYNTAX, ms->token_list->content));
	filename = ((t_token *)ms->token_list->content)->value;
	if (is_redir_token(redir_type))
	{
		token = malloc(sizeof(t_token));
		token->value = ft_strdup(filename);
		token->type = redir_type;
		add_node((t_node **)&group_node->content, token);
	}
	return (OK);
}
