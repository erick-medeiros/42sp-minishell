/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 04:23:02 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/14 22:04:03 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "structs.h"
#include "expander.h"

static int	add_arg(int argc, char ***argv, char *new_arg);
static int	set_redir(t_tok_type redir_type, char *filename, t_cmd *cmd);

int	handle_word_token(t_tree *cmd_node, t_minishell *ms)
{
	char	*expd;
	int		result;
	t_cmd	*cmd;
	t_token	*tok;

	cmd = ((t_cmd *)cmd_node->content);
	tok = ms->token_list->content;
	result = expander(tok->value, &expd, ms);
	if (result != OK)
		return (result);
	result = add_arg(cmd->argc, &cmd->argv, expd);
	if (result != OK)
	{
		destroy_command(cmd);
		return (result);
	}
	cmd->argc++;
	return (OK);
}

static int	add_arg(int argc, char ***argv, char *new_arg)
{
	char	**tmp;
	int		idx;

	tmp = *argv;
	idx = 0;
	*argv = malloc(sizeof(**argv) * (argc + 2));
	if (*argv == NULL)
		return (ERR_ALLOC);
	while (idx < argc)
	{
		(*argv)[idx] = tmp[idx];
		++idx;
	}
	(*argv)[idx++] = new_arg;
	(*argv)[idx] = NULL;
	free(tmp);
	return (OK);
}

int	handle_redirect_token(t_tree *cmd_node, t_minishell *ms)
{
	char		*expd;
	int			result;
	t_cmd		*cmd;
	t_tok_type	redir_type;

	cmd = ((t_cmd *)cmd_node->content);
	redir_type = ((t_token *)ms->token_list->content)->type;
	ms->token_list = remove_node(ms->token_list, del_token_node);
	if (ms->token_list == NULL)
		return (ERR_BAD_SYNTAX);
	if (((t_token *)ms->token_list->content)->type != TOKEN_WORD)
		return (ERR_BAD_SYNTAX);
	result = expander(((t_token *)ms->token_list->content)->value,
			&expd, ms);
	if (result != OK)
		return (result);
	result = set_redir(redir_type, expd, cmd);
	free(expd);
	if (result != OK)
		return (result);
	return (OK);
}

int	enqueue_heredoc(t_tree *cmd_node, t_minishell *ms)
{
	char		*expd;
	int			result;
	t_heredoc	*content;

	ms->token_list = remove_node(ms->token_list, del_token_node);
	if (ms->token_list == NULL)
		return (ERR_BAD_SYNTAX);
	if (((t_token *)ms->token_list->content)->type != TOKEN_WORD)
		return (ERR_BAD_SYNTAX);
	result = expander(((t_token *)ms->token_list->content)->value,
			&expd, ms);
	if (result != OK)
		return (result);
	content = malloc(sizeof(*content));
	if (content == NULL)
		return (ERR_ALLOC);
	content->cmd = cmd_node->content;
	content->delimiter = expd;
	return (enqueue(&ms->heredoc_queue, content));
}

static int	set_redir(t_tok_type redir_type, char *filename, t_cmd *cmd)
{
	if (redir_type == TOKEN_INPUT)
	{
		if (cmd->input != STDIN)
			close(cmd->input);
		cmd->input = open_redirect_fd(filename, TOKEN_INPUT);
		if (cmd->input == -1)
			return (ERR_FILE_OPEN);
	}
	else
	{
		if (cmd->output != STDOUT && cmd->output != STDERR)
			close(cmd->output);
		if (redir_type == TOKEN_OUTPUT)
			cmd->output = open_redirect_fd(filename, TOKEN_OUTPUT);
		else
			cmd->output = open_redirect_fd(filename, TOKEN_APPEND);
		if (cmd->output == -1)
			return (ERR_FILE_OPEN);
	}
	return (OK);
}
