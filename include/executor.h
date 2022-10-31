/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:14:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/31 15:30:15 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include <stddef.h>

// Executor

void	pipeline_executor(t_minishell *minishell, t_pipeline *pipeline);
void	run_command(t_minishell *minishell, t_pipeline *pipeline,
			t_cmd *command);
void	command_exit_status(t_cmd *command);
void	builtins(t_minishell *minishell, t_cmd *command);

// Pipeline

void	open_pipes(t_pipeline *pipeline);
void	connect_pipes(t_pipeline *pipeline, t_cmd *command);
void	close_pipes(t_pipeline *pipeline);

// Subshell

void	subshell(t_minishell *minishell, t_pipeline *pipeline, t_cmd *command);
void	child_process(t_minishell *minishell, t_cmd *command);
void	update_io(t_minishell *minishell, t_cmd *command);
void	exit_process(t_minishell *minishell, int status);
void	process_exit_status(t_cmd *command);

t_tree	*convert_list_to_tree(t_pipeline *pipeline);
void	tree_executor(t_minishell *minishell, t_pipeline *pipeline);

#endif