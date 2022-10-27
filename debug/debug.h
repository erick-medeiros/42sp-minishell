#ifndef DEBUG_H
#define DEBUG_H

#include "minishell.h"

void debug_token(t_minishell *minishell);
void debug_content_fd(int fd, char *prompt, int debug);
void debug_command(t_cmd *command);
void debug_pipeline_fds(t_pipeline *pipeline);

#endif