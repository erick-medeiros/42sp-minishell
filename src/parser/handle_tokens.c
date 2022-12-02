/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 04:23:02 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/02 16:35:15 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "structs.h"
#include <readline/chardefs.h>

static int	save_redirect(t_node **lst, t_tok_type rd_type,
				char *filename, t_minishell *ms);

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

int	handle_group_redirect_token(t_tree *group_node, t_minishell *ms)
{
	char		*filename;
	t_tok_type	rd_type;
	t_tok_type	next_type;
	int			result;

	result = OK;
	rd_type = ((t_token *)ms->token_list->content)->type;
	ms->token_list = remove_node(ms->token_list, del_token_node);
	if (ms->token_list == NULL)
		return (print_token_error(ERR_BAD_SYNTAX, NULL));
	next_type = ((t_token *)ms->token_list->content)->type;
	if (next_type != TOKEN_WORD)
		return (print_token_error(ERR_BAD_SYNTAX, ms->token_list->content));
	filename = ((t_token *)ms->token_list->content)->value;
	result = save_redirect((t_node **)&group_node->content,
			rd_type, filename, ms);
	return (result);
}

static int	save_redirect(t_node **lst, t_tok_type rd_type,
				char *filename, t_minishell *ms)
{
	t_token	*token;

	if (is_redir_token(rd_type))
	{
		token = malloc(sizeof(t_token));
		token->type = rd_type;
		if (rd_type == TOKEN_HEREDOC)
		{
			ms->set_history = FALSE;
			if (process_heredoc(token, filename, &ms->env_list) != OK)
			{
				free(token);
				return (ERR_BAD_SUBST);
			}
		}
		else
			token->value = ft_strdup(filename);
		if (add_node(lst, token) != OK)
		{
			free(token);
			return (ERR_ALLOC);
		}
	}
	return (OK);
}
