/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:04:35 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/06 19:05:41 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

static t_node	*get_prompt_list(t_vlst *env);
static char		*get_user_prompt(void);
static char		*get_hostname_prompt(void);
static char		*get_pwd_prompt(t_vlst *env);

char	*get_prompt(t_vlst *env)
{
	static char	prompt[PROMPT_MAX_LEN];
	char		*tmp;
	t_node		*list;

	list = get_prompt_list(env);
	tmp = convert_list_to_string(list);
	ft_strlcpy(prompt, tmp, ft_strlen(tmp));
	free(tmp);
	return (prompt);
}

static t_node	*get_prompt_list(t_vlst *env)
{
	t_node	*list;

	list = NULL;
	if (ANSI_PROMPT)
		add_node(&list, ft_strdup(GREEN));
	add_node(&list, get_user_prompt());
	if (ANSI_PROMPT)
		add_node(&list, ft_strdup(YELLOW));
	add_node(&list, ft_strdup("@"));
	add_node(&list, get_hostname_prompt());
	add_node(&list, ft_strdup(" "));
	if (ANSI_PROMPT)
		add_node(&list, ft_strdup(BLUE));
	add_node(&list, get_pwd_prompt(env));
	if (ANSI_PROMPT)
		add_node(&list, ft_strdup(WHITE));
	add_node(&list, ft_strdup(" "));
	add_node(&list, ft_itoa(env->last_status));
	add_node(&list, ft_strdup("> "));
	if (ANSI_PROMPT)
		add_node(&list, ft_strdup(RESET));
	add_node(&list, ft_strdup(" "));
	return (list);
}

static char	*get_user_prompt(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
		user = getenv("LOGNAME");
	if (!user)
		user = "(unknown)";
	return (ft_strdup(user));
}

static char	*get_hostname_prompt(void)
{
	char	*hostname;
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("(unknown)"));
	hostname = get_next_line(fd);
	close(fd);
	if (!hostname)
		return (ft_strdup("(unknown)"));
	if (hostname[ft_strlen(hostname) - 1] == '\n')
		hostname[ft_strlen(hostname) - 1] = '\0';
	return (hostname);
}

static char	*get_pwd_prompt(t_vlst *env)
{
	size_t	len;
	char	*homedir;
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_strdup("(unknown)"));
	homedir = expand_variable("$HOME", env);
	if (homedir)
		len = ft_strlen(homedir);
	if (homedir && ft_strncmp(pwd, homedir, len) == 0)
	{
		if (pwd[len] == '/' || pwd[len] == '\0')
		{
			tmp = ft_strjoin("~", &pwd[len]);
			free(pwd);
			pwd = tmp;
		}
	}
	free(homedir);
	return (pwd);
}
