/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:14:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/16 12:12:25 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <stddef.h>

// Executor

void	tree_executor(t_minishell *minishell, t_tree *grandparent,
			t_tree *parent, t_tree *root);
void	sync_tree_execution(t_tree *root, int *exit_status);
void	process_exit_status(t_cmd *command);

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