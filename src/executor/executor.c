/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:12:26 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/14 20:01:01 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "architecture.h"
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void	execute_commands(t_minishell *minishell, t_node *commands);
void	child_process(t_minishell *minishell, t_command *command);

static char	*get_runpath(char **envp, char *cmd_exec)
{
	char	*runpath;
	char	**paths;
	char	*temp;
	int i;

	paths = NULL;
	while (envp != NULL && *envp != NULL && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (envp != NULL && *envp != NULL)
		paths = ft_split(*envp + 5, ':');
	i = -1;
	if (paths != NULL)
		while (paths[++i] != NULL)
		{
			temp = paths[i];
			paths[i] = ft_strjoin(paths[i], "/");
			free(temp);
		}
	if (strrchr(cmd_exec, '/') != NULL) //remover dps
	{
		if (access(cmd_exec, F_OK | X_OK) == 0)
			return (ft_strdup(cmd_exec));
		return (NULL);
	}
	while (paths != NULL && *paths != NULL)
	{
		runpath = ft_strjoin(*paths, cmd_exec);
		if (access(runpath, F_OK | X_OK) == 0)
			return (runpath);
		free(runpath);
		paths++;
	}
	runpath = ft_strjoin("/usr/bin/", cmd_exec);
	if (access(runpath, F_OK | X_OK) == 0)
		return (ft_strdup(runpath));
	free(runpath);
	if (access(cmd_exec, F_OK | X_OK) == 0)
		return (ft_strdup(cmd_exec));
	return (NULL);
}

void	executor(t_minishell *minishell)
{
	int	i;

	i = 0;
	// while (minishell->command_table[i] != NULL)
	// {
		if (minishell->command_table[i]->logical_operator == LOGICAL_COMMAND)
			execute_commands(minishell, minishell->command_table[i]->commands);
		// ++i;
	// }
}

void	execute_commands(t_minishell *minishell, t_node *commands)
{
	t_node	*node;
	t_command *cmd;

	node = commands;
	while (node)
	{
		// printf("node\n");
		cmd = (t_command *) node->content;
		cmd->pid = fork();
		if (cmd->pid < 0)
			write(STDERR, "Error", 5);
		else if (cmd->pid == 0)
			child_process(minishell, cmd);
		else
			node = node->next;
	}
	node = commands;
	while (node)
	{
		cmd = (t_command *) node->content;
		waitpid(cmd->pid, &cmd->exit_code, 0);
		if (WIFEXITED(cmd->exit_code))
			cmd->exit_code = WEXITSTATUS(cmd->exit_code);
		if (cmd->exit_code != 0)
			write(STDOUT, "Error", 5);
		node = node->next;
	}
}

void child_process(t_minishell *minishell, t_command *command)
{
	char	*new_runpath;
	// dup2(command->input, STDIN);
	// dup2(command->output, STDOUT);
	// printf("child_process\n");
	// printf("pathname) %s\n", command->pathname);
	// printf("args 1) %s\n", command->args[0]);
	// printf("args 2) %s\n", command->args[1]);
	// printf("args 3) %s\n", command->args[2]);
	new_runpath = get_runpath(minishell->envp, command->pathname);
	if (new_runpath == NULL)
		exit(0);
	if (execve(new_runpath, command->args, minishell->envp) == -1)
		write(STDERR, "Error", 5);
}
