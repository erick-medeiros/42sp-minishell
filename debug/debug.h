#ifndef DEBUG_H
#define DEBUG_H

#include "minishell.h"
#include "executor.h"

void debug_token(t_minishell *minishell);
void debug_content_fd(int fd, char *prompt, int debug);
void debug_command(t_cmd *command);
void debug_pipeline_fds(t_pipeline *pipeline);
void debug_pipeline_commands(t_pipeline *pipeline);
void debug_tree(t_tree *root);
void debug_queue_cmds(t_queue *cmds);

#endif