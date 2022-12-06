/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 17:18:58 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	parse_token(t_ms *ms, t_tree **tree);
static int	parse_optoken(t_ms *ms, t_tree **tree);

int	parser(t_ms *ms, int result)
{
	if (result == ERR_INCOMP_OP && validate_line_start(ms))
		return (print_token_error(ERR_BAD_SYNTAX, ms->token_list->content));
	result = validate_tokens(ms->token_list);
	while (ms->token_list && result == OK)
	{
		result = parse_token(ms, &(ms->tmp_cmd));
		if (result == OK || result == ERR_INCOMP_OP)
		{
			if (push_postfix(&(ms->opstack), &(ms->cmd_list), ms->tmp_cmd))
				result = ERR_ALLOC;
			else
				ms->tmp_cmd = NULL;
		}
	}
	if (result == OK)
		result = flush_postfix(&(ms->opstack), &(ms->cmd_list));
	return (result);
}

static int	parse_token(t_ms *ms, t_tree **tree)
{
	if (is_optoken(ms->token_list->content))
		return (parse_optoken(ms, tree));
	return (get_command(tree, ms));
}

static int	parse_optoken(t_ms *ms, t_tree **tree)
{
	t_tree_type	tree_type;
	int			result;

	tree_type = tok_to_tree_type((t_token *)ms->token_list->content);
	if (ms->token_list->next == NULL)
	{
		result = new_op_node(tree, tree_type);
		if (result != OK)
			return (result);
		ms->token_list = remove_node(ms->token_list, del_token_node);
		return (ERR_INCOMP_OP);
	}
	if (is_optoken(ms->token_list->next->content))
		return (print_token_error(ERR_BAD_SYNTAX, ms->token_list->content));
	ms->token_list = remove_node(ms->token_list, del_token_node);
	return (new_op_node(tree, tree_type));
}

int	get_command(t_tree **cmd_node, t_ms *ms)
{
	int		result;

	if (ms->token_list == NULL)
		return (OK);
	if (*cmd_node == NULL)
		*cmd_node = new_cmd_node();
	if (*cmd_node == NULL)
		return (ERR_ALLOC);
	while (ms->token_list != NULL
		&& !is_op(tok_to_tree_type((t_token *)ms->token_list->content)))
	{
		result = handle_next_token(*cmd_node, ms);
		if (result != OK)
			return (result);
		ms->token_list = remove_node(ms->token_list, del_token_node);
	}
	return (OK);
}
