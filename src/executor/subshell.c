/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:48:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/18 15:31:34 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "expander.h"
#include "builtins.h"

void	subshell(t_minishell *minishell, t_cmd *command)
{
	int	status;

	handle_signal(SIGINT, command_signal_handler);
	handle_signal(SIGQUIT, command_signal_handler);
	command->pid = fork();
	if (command->pid < 0)
		command->status = error_message(1, (char *[]){strerror(errno), NULL});
	else if (command->pid == 0)
	{
		subshell_redirect(command);
		close_pipeline(minishell->root);
		status = 0;
		command->envp = list_to_envp(&minishell->env_list, NULL, 0);
		if (command->isbuiltin)
			status = execute_builtin(minishell, command);
		else
			status = execute_program(command);
		destroy_minishell(minishell);
		exit(status);
	}
}

int	execute_builtin(t_minishell *ms, t_cmd *cmd)
{
	const char	*cd_err[] = {"too many arguments", NULL};

	if (ft_streq(cmd->argv[0], "echo"))
		cmd->status = builtin_echo(cmd);
	else if (ft_streq(cmd->argv[0], "cd"))
	{
		if (cmd->argc == 2)
			cmd->status = builtin_cd(cmd->argv[1], &ms->env_list);
		else
			cmd->status = error_message(1, (char **)cd_err);
	}
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

int	execute_program(t_cmd *command)
{
	if (!command->pathname)
	{
		ft_putstr_fd(command->argv[0], STDERR);
		ft_putendl_fd(": command not found", STDERR);
		return (127);
	}
	execve(command->pathname, command->argv, command->envp);
	return (error_message(1, (char *[]){command->argv[0], strerror(errno), 0}));
}

void	subshell_redirect(t_cmd *command)
{
	dup2(command->piping[READ_PIPE], STDIN);
	dup2(command->piping[WRITE_PIPE], STDOUT);
	dup2(command->input, STDIN);
	dup2(command->output, STDOUT);
	if (command->input > STDERR)
		close(command->input);
	if (command->output > STDERR)
		close(command->output);
	command->input = STDIN;
	command->output = STDOUT;
}
