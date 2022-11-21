/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:14:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/21 03:49:17 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_BONUS_H
# define EXECUTOR_BONUS_H

# include "minishell_bonus.h"

// Executor

void	tree_executor(t_minishell *ms, t_tree *root, int input, int output);
void	sync_tree_execution(t_tree *root, int *exit_status, int *coredump);

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

int		execute_command(t_minishell *ms, t_cmd *cmd, t_vlst *env);
void	subshell(t_minishell *ms, t_cmd *cmd, t_vlst *env);
int		execute_builtin(t_minishell *ms, t_cmd *cmd, t_vlst *env);
int		execute_program(t_cmd *cmd);
int		command_exit_status(t_cmd *cmd, int *coredump);

// Error handling
void	print_signal_error(int exit_status, int coredump);
int		command_not_found_handle(char *name);

#endif
