#include "minishell.h"
#include "parser.h"
#include "structs.h"

static int	set_redir(t_tok_type redir_type, char *filename, t_cmd *cmd);

int	handle_word_token(t_token *tok, t_tree *cmd_node, t_minishell *ms)
{
	char	*expd;
	int		result;
	t_cmd	*cmd;

	cmd = ((t_cmd *)cmd_node->content);
	if (cmd->argc == 0)
		result = expand_filename(tok->value, &expd, ms);
	else
		result = expand_vars(tok->value, &expd, ms);
	if (result)
		return (result);
	cmd->argv[cmd->argc++] = expd;
	return (OK);
}

int	handle_redirect_token(t_node **toks, t_tree *cmd_node, t_minishell *ms)
{
	char		*expd;
	int			result;
	t_cmd		*cmd;
	t_tok_type	redir_type;

	cmd = ((t_cmd *)cmd_node->content);
	redir_type = ((t_token *)(*toks)->content)->type;
	*toks = remove_node(*toks, del_token_node);
	if (((t_token *)(*toks)->content)->type != TOKEN_WORD)
		return (ERR_BAD_SYNTAX);
	result = expand_filename(((t_token *)(*toks)->content)->value, &expd, ms);
	if (result)
		return (result);
	result = set_redir(redir_type, expd, cmd);
	if (result)
		return (result);
	return (OK);
}

int	enqueue_heredoc(t_node **toks, t_tree *cmd_node, t_minishell *ms)
{
	char		*expd;
	int			result;
	t_heredoc	*content;

	*toks = remove_node(*toks, del_token_node);
	if (((t_token *)(*toks)->content)->type != TOKEN_WORD)
		return (ERR_BAD_SYNTAX);
	result = expand_filename(((t_token *)(*toks)->content)->value, &expd, ms);
	if (result)
		return (result);
	content = malloc(sizeof(*content));
	if (content == NULL)
		return (ERR_ALLOC);
	content->cmd = cmd_node->content;
	content->delimiter = expd;
	return (enqueue(&ms->heredoc_queue, content));
}

// TODO: check bash behaviour with multiple redirs and invalid files
// TODO: check if files should indeed be closed
static int	set_redir(t_tok_type redir_type, char *filename, t_cmd *cmd)
{

	if (redir_type == TOKEN_INPUT)
	{
		if (cmd->output != STDIN)
			close(cmd->output);
		cmd->input = open_fd(filename, IN_MODE);
		if (cmd->output == -1)
			return (ERR_FILE_OPEN);
	}
	else
	{
		if (cmd->output != STDOUT && cmd->output != STDERR)
			close(cmd->output);
		if (redir_type == TOKEN_OUTPUT)
			cmd->output = open_fd(filename, OUT_MODE);
		else
			cmd->output = open_fd(filename, APPEND_MODE);
		if (cmd->output == -1)
			return (ERR_FILE_OPEN);
	}
	return (OK);
}
