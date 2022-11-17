/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:14:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/17 17:49:01 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

// Executor

void	tree_executor(t_minishell *minishell, t_tree *grandparent,
			t_tree *parent, t_tree *root);
void	sync_tree_execution(t_tree *root, int *exit_status);
int		command_exit_status(t_cmd *cmd);

// Expansor

int		command_expansion(t_minishell *ms, t_cmd *cmd);

// Redirect

int		command_redirect(t_cmd *cmd);
int		open_redirect_fd(char *pathname, int token_type);

// Search

int		command_search(t_cmd *command, t_vlst *env_list);

// Pipeline

void	connect_pipeline(t_cmd *cmd, t_tree *grandparent, t_tree *parent,
			t_tree *node);
void	close_pipeline(t_tree *root);

// Subshell

void	subshell(t_minishell *minishell, t_cmd *command);
void	subshell_redirect(t_cmd *command);

// Execute

int		execute_command(t_minishell *minishell, t_cmd *command);
int		execute_builtin(t_minishell *minishell, t_cmd *command);
int		execute_program(t_cmd *command);

#endif