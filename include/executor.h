/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:14:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/19 11:08:35 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

// Executor

void	tree_executor(t_minishell *ms, t_tree *root, int input, int output);
void	sync_tree_execution(t_tree *root, int *exit_status, int *coredump);

// Expander

int		command_expansion(t_minishell *ms, t_cmd *cmd);

// Redirect

int		command_redirect(t_cmd *cmd);
int		open_redirect_fd(char *pathname, int token_type);

// Search

int		command_search(t_cmd *command, t_vlst *env_list);

// Pipeline

void	close_pipeline(t_tree *root);

// Command

int		execute_command(t_minishell *minishell, t_cmd *command);
void	subshell(t_minishell *minishell, t_cmd *command);
int		execute_builtin(t_minishell *minishell, t_cmd *command);
int		execute_program(t_cmd *command);
int		command_exit_status(t_cmd *cmd, int *coredump);

// Error handling
void	print_signal_error(int exit_status, int coredump);
int		command_not_found_handle(char *name);

#endif
