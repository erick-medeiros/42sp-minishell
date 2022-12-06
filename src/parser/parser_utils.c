/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:57:23 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/06 18:23:55 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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
	else
		ft_putstr_fd("\n", STDERR);
	return (status);
}

int	validate_line_start(t_ms *ms)
{
	if (ms->token_list)
		return (is_optoken(ms->token_list->content));
	return (OK);
}
