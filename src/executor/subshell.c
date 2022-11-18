/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/18 17:21:38 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expander.h"
#include "builtins.h"

void	subshell(t_minishell *minishell, t_cmd *command)
{
	handle_signal(SIGINT, command_signal_handler);
	handle_signal(SIGQUIT, command_signal_handler);
	command->pid = fork();
	if (command->pid < 0)
		command->status = error_message1(1, strerror(errno));
	else if (command->pid == 0)
	{
		dup2(command->piping[READ_PIPE], STDIN);
		dup2(command->piping[WRITE_PIPE], STDOUT);
		dup2(command->input, STDIN);
		dup2(command->output, STDOUT);
		close_safe(command->input);
		close_safe(command->output);
		command->input = STDIN;
		command->output = STDOUT;
		close_pipeline(minishell->root);
		command->envp = list_to_envp(&minishell->env_list, NULL, 0);
		if (command->isbuiltin)
			command->status = execute_builtin(minishell, command);
		else
			command->status = execute_program(command);
		builtin_exit(command->status, minishell, NULL);
	}
}

int	execute_builtin(t_minishell *ms, t_cmd *cmd)
{
	if (ft_streq(cmd->argv[0], "echo"))
		cmd->status = builtin_echo(cmd);
	else if (ft_streq(cmd->argv[0], "cd"))
		cmd->status = builtin_cd(cmd->argc, cmd->argv, &ms->env_list);
	else if (ft_streq(cmd->argv[0], "pwd"))
		cmd->status = builtin_pwd(cmd->output);
	else if (ft_streq(cmd->argv[0], "export"))
		cmd->status = builtin_export(cmd->argc, cmd->argv, &ms->env_list);
	else if (ft_streq(cmd->argv[0], "unset"))
		cmd->status = builtin_unset(cmd->argc, cmd->argv, &ms->env_list);
	else if (ft_streq(cmd->argv[0], "env"))
		cmd->status = builtin_env(cmd->output, &ms->env_list);
	else if (ft_streq(cmd->argv[0], "exit"))
		builtin_exit(ms->exit_status, ms, cmd);
	return (cmd->status);
}

int	execute_program(t_cmd *cmd)
{
	if (!cmd->pathname)
		return (command_not_found_handle(cmd->argv[0]));
	execve(cmd->pathname, cmd->argv, cmd->envp);
	return (error_message2(1, cmd->argv[0], strerror(errno)));
}
