/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:57:23 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/05 20:42:48 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "structs.h"

static int	print_token_type_error(int status, t_tok_type tok_type);

int	handle_next_token_error(t_ms *ms)
{
	t_token		*tok;

	tok = ((t_token *)(ms->token_list->content));
	if (tok->type == TOKEN_DQINCOMP)
		return (ERR_INCOMP_DQ);
	if (tok->type == TOKEN_SQINCOMP)
		return (ERR_INCOMP_SQ);
	if (tok->type == TOKEN_BRCINCOMP)
		return (ERR_INCOMP_BRC);
	if (tok->type == TOKEN_DQBRACE)
		return (ERR_INCOMP_BRC_DQ);
	if (tok->type == TOKEN_SQBRACE)
		return (ERR_INCOMP_BRC_SQ);
	return (error_message1(ERR_BAD_SYNTAX, "Invalid token"));
}

int	print_token_error(int status, t_token *tok)
{
	if (tok == NULL)
	{
		ft_putstr_fd("minishell: syntax error", STDERR);
		ft_putstr_fd(" near unexpected token `newline'\n", STDERR);
	}
	else if (tok->type == TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error", STDERR);
		ft_putstr_fd(" near unexpected token `", STDERR);
		ft_putstr_fd(tok->value, STDERR);
		ft_putstr_fd("'\n", STDERR);
	}
	else
		return (print_token_type_error(status, tok->type));
	return (status);
}

static int	print_token_type_error(int status, t_tok_type tok_type)
{
	ft_putstr_fd("minishell: syntax error", STDERR);
	if (tok_type == TOKEN_PIPE)
		ft_putstr_fd(" near unexpected token `|'\n", STDERR);
	else if (tok_type == TOKEN_AND)
		ft_putstr_fd(" near unexpected token `&&'\n", STDERR);
	else if (tok_type == TOKEN_OR)
		ft_putstr_fd(" near unexpected token `||'\n", STDERR);
	else if (tok_type == TOKEN_NL)
		ft_putstr_fd(" near unexpected token `newline'\n", STDERR);
	else if (tok_type == TOKEN_APPEND)
		ft_putstr_fd(" near unexpected token `>>'\n", STDERR);
	else if (tok_type == TOKEN_INPUT)
		ft_putstr_fd(" near unexpected token `<'\n", STDERR);
	else if (tok_type == TOKEN_OUTPUT)
		ft_putstr_fd(" near unexpected token `>'\n", STDERR);
	else if (tok_type == TOKEN_HEREDOC)
		ft_putstr_fd(" near unexpected token `<<'\n", STDERR);
	else if (tok_type == TOKEN_OPARENTHESIS)
		ft_putstr_fd(" near unexpected token `('\n", STDERR);
	else if (tok_type == TOKEN_CPARENTHESIS)
		ft_putstr_fd(" near unexpected token `)'\n", STDERR);
	else
		ft_putstr_fd("\n", STDERR);
	return (status);
}

int	validate_line_start(t_ms *ms)
{
	t_tree_type	t;

	if (ms->token_list)
	{
		if (ms->cmd_list.front == NULL && ms->tmp_cmd == NULL)
		{
			return (is_optoken(ms->token_list->content)
				|| ((t_token *)ms->token_list->content)->type
				== TOKEN_CPARENTHESIS);
		}
		if (ms->opstack)
		{
			t = ((t_tree *) ms->opstack->content)->type;
			if (t == TREE_TYPE_AND || t == TREE_TYPE_OR || t == TREE_TYPE_PIPE)
				return (is_optoken(ms->token_list->content));
		}
		return (!(is_optoken(ms->token_list->content)
			|| ((t_token *)ms->token_list->content)->type
			== TOKEN_CPARENTHESIS));
	}
	return (OK);
}

int	handle_close_parenthesis(t_ms *ms, t_tree_type tree_type, t_tree **tree)
{
	int	result;

	ms->num_pars--;
	ms->token_list = remove_node(ms->token_list, del_token_node);
	result = new_op_node(tree, tree_type);
	if (result != OK)
		return (result);
	while (ms->token_list
		&& is_redir_token(((t_token *)ms->token_list->content)->type))
	{
		result = handle_group_redirect_token(*tree, ms);
		if (result != OK)
			return (result);
		ms->token_list = remove_node(ms->token_list, del_token_node);
	}
	return (OK);
}
