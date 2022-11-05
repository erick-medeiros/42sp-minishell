/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/05 04:24:09 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int			parse_token(t_minishell *ms, t_node **tmp_stack,
						t_node	**cmds, int cmd_num);
static t_tree_type	tok_to_tree_type(t_token *tok);

int	parser(t_minishell *ms, int cmd_num)
{
	t_node		*tmp_stack;
	t_node		*cmds;
	int			result;

	result = OK;
	tmp_stack = NULL;
	cmds = NULL;
	if (ms->token_list
		&& is_op(tok_to_tree_type(((t_token *)ms->token_list->content))))
		return (ERR_BAD_SYNTAX);
	while (ms->token_list && result == OK)
		result = parse_token(ms, &tmp_stack, &cmds, cmd_num);
	flush_infix(&tmp_stack, &cmds);
	return (result);
}

static int	parse_token(t_minishell *ms, t_node **tmp_stack,
				t_node	**cmds, int cmd_num)
{
	t_tree		*tree;
	t_tree_type	tree_type;
	int			result;

	tree = NULL;
	tree_type = tok_to_tree_type((t_token *)ms->token_list->content);
	if (is_op(tree_type))
	{
		if (ms->token_list == NULL)
			return (ERR_INCOMP_PIPE);
		if (is_op(tok_to_tree_type(((t_token *)ms->token_list->content))))
			return (ERR_BAD_SYNTAX);
		result = new_op_node(&tree, tree_type);
	}
	else
		result = get_command(&ms->token_list, &tree, ms, cmd_num);
	if (result != ERR_BAD_SYNTAX && result != ERR_ALLOC)
	{
		if (push_infix(tmp_stack, cmds, tree))
			return (ERR_ALLOC);
	}
	return (result);
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
