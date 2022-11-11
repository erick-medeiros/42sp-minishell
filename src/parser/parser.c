/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/10 18:57:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "structs.h"
#include "debug.h"

static int			parse_token(t_minishell *ms, t_tree **tree, int cmd_num);
static t_tree_type	tok_to_tree_type(t_token *tok);

int	parser(t_minishell *ms, int cmd_num)
{
	static t_tree	*tree = NULL;
	t_node			*tmp_stack;
	int				result;

	result = OK;
	tmp_stack = NULL;
	if (ms->token_list
		&& is_op(tok_to_tree_type(((t_token *)ms->token_list->content))))
		return (ERR_BAD_SYNTAX);
	while (ms->token_list && result == OK)
	{
		result = parse_token(ms, &tree, cmd_num);
		if (result == OK || result == ERR_INCOMP_PIPE)
		{
			if (push_postfix(&tmp_stack, &ms->cmd_list, tree))
				return (ERR_ALLOC);
			tree = NULL;
		}
	}
	if (result == OK)
		result = flush_postfix(&tmp_stack, &ms->cmd_list);
	return (result);
}

static int	parse_token(t_minishell *ms, t_tree **tree, int cmd_num)
{
	t_tree_type	tree_type;
	int			result;

	tree_type = tok_to_tree_type((t_token *)ms->token_list->content);
	if (is_op(tree_type))
	{
		if (ms->token_list->next == NULL)
		{
			result = new_op_node(tree, tree_type);
			if (result != OK)
				return (result);
			ms->token_list = remove_node(ms->token_list, del_token_node);
			return (ERR_INCOMP_PIPE);
		}
		if (is_op(tok_to_tree_type(ms->token_list->next->content)))
			return (ERR_BAD_SYNTAX);
		result = new_op_node(tree, tree_type);
		ms->token_list = remove_node(ms->token_list, del_token_node);
	}
	else
		result = get_command(tree, ms, cmd_num);
	return (result);
}

int	get_command(t_tree **cmd_node, t_minishell *ms, int num)
{
	int		result;

	if (ms->token_list == NULL)
		return (OK);
	if (*cmd_node == NULL)
		*cmd_node = new_cmd_node(num);
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
	initialize_command((*cmd_node)->content, ms);
	return (OK);
}

static t_tree_type	tok_to_tree_type(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
		return (TREE_TYPE_PIPE);
	return (TREE_TYPE_CMD);
}

int	is_op(t_tree_type t)
{
	return (t == TREE_TYPE_PIPE);
}
