/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internals.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:14:10 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/21 19:20:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_INTERNALS_H
# define EXECUTOR_INTERNALS_H

# include "minishell.h"

void	child_process(t_minishell *minishell, t_command *command);
void	exit_process(t_minishell *minishell, int status);
void	process_exit_status(t_command *command);

#endif