/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:57:23 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/16 18:41:52 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "structs.h"
#include <unistd.h>

int	handle_next_token(t_tree *cmd_node, t_minishell *ms)
{
	t_token	*tok;

	tok = ((t_token *)(ms->token_list->content));
	if (tok->type == TOKEN_PIPE)
		return (OK);
	if (tok->type == TOKEN_WORD)
		return (handle_word_token(cmd_node, ms));
	if (tok->type == TOKEN_INPUT || tok->type == TOKEN_OUTPUT
		|| tok->type == TOKEN_APPEND)
		return (handle_redirect_token(cmd_node, ms));
	if (tok->type == TOKEN_HEREDOC)
		return (enqueue_heredoc(cmd_node, ms));
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
	return (ERR_BAD_SYNTAX);
}

t_tree	*new_cmd_node(int num)
{
	t_tree	*cmd_node;

	cmd_node = malloc(sizeof(*cmd_node));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = TREE_TYPE_CMD;
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	cmd_node->content = new_command(num);
	return (cmd_node);
}

int	new_op_node(t_tree	**op_node, t_tree_type op_type)
{
	*op_node = malloc(sizeof(**op_node));
	if (!op_node)
		return (ERR_ALLOC);
	(*op_node)->type = op_type;
	(*op_node)->left = NULL;
	(*op_node)->right = NULL;
	(*op_node)->content = NULL;
	return (OK);
}

void	process_heredoc(t_queue *heredoc_queue)
{
	t_heredoc	*heredoc;

	while (heredoc_queue->front != NULL)
	{
		heredoc = dequeue(heredoc_queue);
		if (heredoc->cmd->input != STDIN)
			close(heredoc->cmd->input);
		heredoc->cmd->input = here_doc(heredoc->delimiter);
		free(heredoc->delimiter);
		free(heredoc);
	}
}
