/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:32:33 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 21:24:36 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "structs.h"

t_bool	matching(char *match, char **match_list, int i, struct dirent *direntp)
{
	char	*tmp;
	t_bool	check;

	check = TRUE;
	if (i == 0 && match[0] != '*')
	{
		if (ft_strncmp(direntp->d_name, match_list[i],
				ft_strlen(match_list[i])))
			check = FALSE;
	}
	else if (!match_list[i + 1] && match[ft_strlen(match) - 1] != '*')
	{
		tmp = &direntp->d_name[ft_strlen(direntp->d_name)
			- ft_strlen(match_list[i])];
		if (ft_strncmp(tmp, match_list[i], ft_strlen(tmp)))
			check = FALSE;
	}
	else if (!ft_strnstr(direntp->d_name, match_list[i],
			ft_strlen(direntp->d_name)))
		check = FALSE;
	return (check);
}

t_bool	pattern_matching(char *match, struct dirent *direntp)
{
	char	**matchs;
	int		i;
	t_bool	check;

	if (direntp->d_name[0] == '.' && match[0] != '.')
		return (FALSE);
	matchs = ft_split(match, '*');
	check = TRUE;
	i = 0;
	while (matchs[i] && check)
	{
		check = matching(match, matchs, i, direntp);
		++i;
	}
	free_string_list(matchs);
	return (check);
}

t_node	*directory_files(char *match)
{
	struct dirent	*direntp;
	DIR				*dirp;
	t_node			*list;

	list = NULL;
	dirp = opendir(".");
	if (dirp == NULL)
		panic_error("Cannot open directory");
	while (1 && dirp)
	{
		errno = 0;
		direntp = readdir(dirp);
		if (!direntp)
		{
			if (errno != 0)
				panic_error(strerror(errno));
			break ;
		}
		if (pattern_matching(match, direntp))
			add_node(&list, ft_strdup(direntp->d_name));
	}
	closedir(dirp);
	return (list);
}

void	sort_list(t_node *list)
{
	t_node	*node;
	t_node	*node2;
	void	*content;

	content = NULL;
	node = list;
	while (node)
	{
		node2 = node->next;
		while (node2)
		{
			if (ft_strncmp(node->content, node2->content,
					ft_strlen(node->content)) > 0)
			{
				content = node->content;
				node->content = node2->content;
				node2->content = content;
			}
			node2 = node2->next;
		}
		node = node->next;
	}
}

char	*expand_filename(char *match)
{
	t_node	*list;
	t_node	*node;
	char	*result;

	result = NULL;
	if (!match)
		return (NULL);
	if (!ft_strchr(match, '*'))
		return (ft_strdup(match));
	list = directory_files(match);
	sort_list(list);
	node = list;
	while (node)
	{
		ft_strappend(&result, node->content);
		node = node->next;
		if (node)
			ft_strappend(&result, " ");
	}
	clear_list(list, free);
	if (result)
		return (result);
	else
		return (ft_strdup(match));
}
