/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/21 03:55:47 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "executor_bonus.h"
#include "expander_bonus.h"
#include "builtins_bonus.h"

int	execute_command(t_minishell *ms, t_cmd *cmd, t_vlst *env)
{
	cmd->status = command_expansion(cmd, env);
	if (cmd->status != OK)
		return (cmd->status);
	cmd->status = command_redirect(cmd);
	if (cmd->status != OK)
		return (cmd->status);
	if (cmd->argc == 0)
		return (0);
	cmd->status = command_search(cmd, env);
	if (cmd->status != OK && cmd->status != ERR_CMD_NOT_FOUND)
		return (cmd->status);
	if (cmd->isbuiltin && !ms->pipeline)
		cmd->status = execute_builtin(ms, cmd, env);
	else
		subshell(ms, cmd, env);
	return (0);
}

void	subshell(t_minishell *ms, t_cmd *cmd, t_vlst *env)
{
	handle_signal(SIGINT, command_signal_handler);
	handle_signal(SIGQUIT, command_signal_handler);
	cmd->pid = fork();
	if (cmd->pid < 0)
		cmd->status = error_message2(1, "fork failed", strerror(errno));
	else if (cmd->pid == 0)
	{
		dup2(cmd->input, STDIN);
		dup2(cmd->output, STDOUT);
		close_safe(cmd->input);
		close_safe(cmd->output);
		cmd->input = STDIN;
		cmd->output = STDOUT;
		close_pipeline(ms->root);
		cmd->envp = list_to_envp(env, NULL, 0);
		if (cmd->isbuiltin)
			cmd->status = execute_builtin(ms, cmd, env);
		else
			cmd->status = execute_program(cmd);
		builtin_exit(cmd->status, ms, NULL);
	}
}

int	execute_builtin(t_minishell *ms, t_cmd *cmd, t_vlst *env)
{
	if (ft_streq(cmd->argv[0], "echo"))
		cmd->status = builtin_echo(cmd->output, cmd->argv);
	else if (ft_streq(cmd->argv[0], "cd"))
		cmd->status = builtin_cd(cmd->argc, cmd->argv, env);
	else if (ft_streq(cmd->argv[0], "pwd"))
		cmd->status = builtin_pwd(cmd->output);
	else if (ft_streq(cmd->argv[0], "export"))
		cmd->status = builtin_export(cmd->argc, cmd->argv, env);
	else if (ft_streq(cmd->argv[0], "unset"))
		cmd->status = builtin_unset(cmd->argc, cmd->argv, env);
	else if (ft_streq(cmd->argv[0], "env"))
		cmd->status = builtin_env(cmd->output, env);
	else if (ft_streq(cmd->argv[0], "exit"))
		builtin_exit(env->last_status, ms, cmd);
	return (cmd->status);
}

int	execute_program(t_cmd *cmd)
{
	if (!cmd->pathname)
		return (command_not_found_handle(cmd->argv[0]));
	execve(cmd->pathname, cmd->argv, cmd->envp);
	return (error_message2(1, cmd->argv[0], strerror(errno)));
}

int	command_exit_status(t_cmd *cmd, int *coredump)
{
	if (cmd->pid > 0)
	{
		waitpid(cmd->pid, &cmd->status, 0);
		if (WIFEXITED(cmd->status))
			cmd->status = WEXITSTATUS(cmd->status);
		else if (WIFSIGNALED(cmd->status))
		{
			if (coredump)
				*coredump = WCOREDUMP(cmd->status);
			cmd->status = 128 + WTERMSIG(cmd->status);
		}
	}
	return (cmd->status);
}
