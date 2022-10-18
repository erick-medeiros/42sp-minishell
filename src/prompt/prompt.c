/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/18 13:49:47 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_is_equal(char *cmd, char *str)
{
	int	len;

	len = ft_max(ft_strlen(cmd), ft_strlen(str));
	if (ft_strncmp(cmd, str, len) == 0)
		return (TRUE);
	return (FALSE);
}

int	command_ends_with(char *cmd, char c)
{
	int	index;

	if (cmd == NULL)
		return (FALSE);
	index = ft_strlen(cmd) - 1;
	if (index < 0)
		return (FALSE);
	if (cmd[index] == c)
		return (TRUE);
	return (FALSE);
}

char	*get_content_fd(int fd)
{
	char	buffer[100];
	int		i;
	int		bytes;
	char	*tmp;
	char	*content;

	i = -1;
	while (++i < 100)
		buffer[i] = '\0';
	content = ft_strjoin("", "");
	while (TRUE)
	{
		bytes = read(fd, buffer, 100);
		if (bytes <= 0)
			break ;
		tmp = content;
		content = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	return (content);
}

// debug return heredoc and endsinpipe
void	temp_function(int fd, char *prompt, int debug)
{
	char	*content;

	content = get_content_fd(fd);
	if (debug == 1)
		printf("%s", content);
	else
		printf("exec: %s %s\n", prompt, content);
	free(content);
	close(fd);
}

void	temp_function2(char *prompt)
{
	char	**list;
	int		i;

	list = ft_split_cmd(prompt, ' ');
	i = 0;
	while (list && list[i])
	{
		printf("%s ", list[i]);
		++i;
	}
	printf("\n");
}

void	debug_token(t_minishell *minishell)
{
	t_node	*current;

	current = minishell->token_list;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}

void	temp_call(char *prompt)
{
	int		fd;

	if (command_is_equal(prompt, "here_doc"))
	{
		fd = here_doc("EOF");
		temp_function(fd, prompt, 1);
	}
	else if (command_ends_with(prompt, '|'))
	{
		fd = ends_in_pipe();
		temp_function(fd, prompt, 2);
	}
	else
		builtins(prompt);
}

void	miniprompt(t_minishell *minishell)
{
	char	*prompt;

	while (1)
	{
		prompt = readline(PROMPT_STRING);
		if (!prompt)
			break ;
		minishell->token_list = lexer(prompt);
		free(prompt);
		parser(minishell);
		executor(minishell);
		free_minishell(minishell);
	}
}
