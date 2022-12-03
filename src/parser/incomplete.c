# include "minishell.h"

void	del_incomplete_tree_node(void *tree)
{
	t_cmd	*cmd;

	cmd = ((t_tree *)tree)->content;
	clear_list(cmd->word_tokens, del_token_node);
	clear_list(cmd->redirect, del_token_node);
	free(cmd);
	free(tree);
}

void	clear_incomplete(t_node **opstack, t_tree **tree)
{
	clear_list(*opstack, del_incomplete_tree_node);
	*opstack = NULL;
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
