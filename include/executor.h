/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:14:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/22 15:16:08 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

// Executor

void	etree_executor(t_exec *exec, t_vlst *env, t_etree *node);
void	group_executor(t_exec *exec, t_vlst *env, t_etree *node);
void	pipeline_sync(t_queue *queue);
void	destroy_exec(t_exec *exec);

// Expander

int		command_expansion(t_cmd *cmd, t_vlst *env);

// Redirect

int		command_redirect(t_cmd *cmd);
int		open_redirect_fd(char *pathname, int token_type);

// Search

int		command_search(t_cmd *cmd, t_vlst *env);

// Pipeline

void	close_pipeline(t_tree *root);

// Command

int		execute_command(t_exec *exec, t_etree *node, t_vlst *env);
void	subshell(t_exec *exec, t_etree *node, t_vlst *env);
int		execute_builtin(t_cmd *cmd, t_vlst *env);
int		execute_program(t_etree *node, t_vlst *env);
int		command_exit_status(t_cmd *cmd, int *coredump);

// Error handling
void	print_signal_error(int exit_status, int coredump);
int		command_not_found_handle(char *name);

#endif
