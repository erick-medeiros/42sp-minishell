#ifndef DEBUG_H
#define DEBUG_H

#include "libft.h"
#include "minishell.h"

void debug_token(t_node *token_list);
void debug_command(t_cmd *command);
void debug_tree(t_tree *root);
void debug_queue_cmds(t_queue *cmds);

#endif