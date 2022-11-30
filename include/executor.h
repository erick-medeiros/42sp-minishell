/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:14:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/30 09:30:42 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

// Executor

void	tree_executor(t_exec *exec, t_tree *node, int in, int out);
void	tree_pipe_executor(t_exec *exec, t_tree *node, int in, int out);
void	tree_list_executor(t_exec *exec, t_tree *node, int in, int out);
void	tree_group_executor(t_exec *exec, t_tree *node, int in, int out);
void	destroy_exec(t_exec *exec);

// Expander

int		command_expansion(t_cmd *cmd, t_vlst *env);

// Redirect

int		command_redirect(t_cmd *cmd);
int		open_redirect_fd(char *pathname, int token_type);

// Search

int		command_search(t_cmd *cmd, t_vlst *env);

// Pipeline

void	execution_sync(t_exec *exec);
void	close_pipeline(t_tree *root);

// Command

int		execute_command(t_exec *exec, t_cmd *cmd);
void	execute_in_subshell(t_exec *exec, t_cmd *cmd);
int		execute_builtin(t_exec *exec, t_cmd *cmd);
int		execute_program(t_exec *exec, t_cmd *cmd);

// Error handling
void	print_signal_error(int exit_status, int coredump);
int		command_not_found_handle(char *name);

#endif
