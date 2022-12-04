/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:57:23 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/04 09:41:09 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	handle_next_token_error(t_ms *ms);
static int	print_token_type_error(int status, t_tok_type tok_type);

int	handle_next_token(t_tree *cmd_node, t_ms *ms)
{
	t_token		*tok;

	tok = ((t_token *)(ms->token_list->content));
	if (tok->type == TOKEN_OPARENTHESIS || tok->type == TOKEN_CPARENTHESIS)
		return (OK);
	if (tok->type == TOKEN_WORD)
		return (handle_word_token(cmd_node, ms));
	if (tok->type == TOKEN_INPUT || tok->type == TOKEN_OUTPUT
		|| tok->type == TOKEN_APPEND || tok->type == TOKEN_HEREDOC)
		return (handle_redirect_token(cmd_node, ms));
	return (handle_next_token_error(ms));
}

static int	handle_next_token_error(t_ms *ms)
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
	ms->env_list.last_status = 2;
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
