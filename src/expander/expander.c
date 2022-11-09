/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:08:48 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/09 01:25:31 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

int	find_env_var(void *str, void *var)
{
	if (command_is_equal(str, ((t_var *)var)->name))
		return (0);
	return (1);
}

static int	count_replace(char *str, int start)
{
	int	i;

	i = start;
	++i;
	if (str[i] == '$')
		++i;
	else if (str[i] == '{')
	{
		while (str[i] && str[i] != '}')
			++i;
		if (str[i] == '}')
			++i;
	}
	else
		while (str[i] && str[i] != ' ' && str[i] != '$')
			++i;
	return (i);
}

static char	*expand_variable(t_vlst *env_list, char *str, int start, int end)
{
	char	*expand;
	t_node	*node;
	int		ignore;
	int		len;

	len = end - start;
	ignore = 0;
	if (str[start + ignore] == '$')
		++ignore;
	if (str[start + ignore] == '{')
	{
		++ignore;
		--len;
	}
	len -= ignore;
	expand = ft_strdup(&str[start + ignore]);
	expand[len] = '\0';
	node = find_node_by_content(env_list->list, expand, find_env_var);
	free(expand);
	if (!node)
		return (NULL);
	return (ft_strdup((((t_var *)node->content)->val)));
}

static int	concat_expanded(char **str, int start, int end, char *expanded)
{
	char	*next;
	char	*previous;
	char	*concat;
	int		len;

	previous = *str;
	previous[start] = '\0';
	next = &previous[end];
	concat = ft_strjoin(previous, expanded);
	len = ft_strlen(concat);
	*str = ft_strjoin(concat, next);
	free(concat);
	free(expanded);
	free(previous);
	return (len);
}

char	*expander_vars(t_vlst *env_list, char *str)
{
	char	*expanded;
	int		i;
	int		start;
	int		end;

	if (!str)
		return (str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i;
			end = count_replace(str, start);
			expanded = expand_variable(env_list, str, start, end);
			if (!expanded && (end - start) == 1)
				++i;
			else
				i = concat_expanded(&str, start, end, expanded);
		}
		else
			++i;
	}
	return (str);
}
