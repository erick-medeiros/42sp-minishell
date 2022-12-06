/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incomplete_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:43:34 by gmachado          #+#    #+#             */
/*   Updated: 2022/12/06 15:28:12 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	del_incomplete_tree_node(void *tree)
{
	t_cmd	*cmd;

	if (((t_tree *)tree)->type == TREE_TYPE_CMD
		|| ((t_tree *)tree)->type == TREE_TYPE_GROUP)
	{
		cmd = ((t_tree *)tree)->content;
		if (cmd->word_tokens)
			clear_list(cmd->word_tokens, del_token_node);
		if (cmd->redirect)
			clear_list(cmd->redirect, del_token_node);
		free(cmd);
	}
	free(tree);
}

void	clear_incomplete(t_node **opstack, t_tree **tree)
{
	if (*opstack)
		clear_list(*opstack, del_incomplete_tree_node);
	*opstack = NULL;
	if (*tree)
		del_incomplete_tree_node(*tree);
	*tree = NULL;
}

t_bool	*init_incomplete(void)
{
	rl_done = FALSE;
	rl_event_hook = event;
	handle_signal(SIGINT, incomplete_handler);
	return (incomplete_signal_receiver(FALSE));
}
