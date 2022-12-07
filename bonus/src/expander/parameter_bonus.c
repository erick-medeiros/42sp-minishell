/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:08:48 by eandre-f          #+#    #+#             */
/*   Updated: 2022/12/07 18:43:59 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_bonus.h"
#include "builtins_bonus.h"
#include "minishell_bonus.h"

static int	parameter_size(char *str);
static char	*get_parameter_name(char *parameter);

char	*parameter_expansion(char *src, t_vlst *env)
{
	int		i;
	int		quote;
	t_node	*list;
	int		start;

	list = NULL;
	quote = 0;
	i = 0;
	start = 0;
	while (src[i])
	{
		quote = update_quote(src[i], quote);
		if (src[i] == '$' && (!quote || quote == DOUBLE_QUOTE))
		{
			add_node(&list, ft_strndup(&src[start], i - start));
			add_node(&list, expand_parameter(&src[i], quote, env));
			i += parameter_size(&src[i]);
			start = i;
		}
		else
			++i;
	}
	add_node(&list, ft_strdup(&src[start]));
	return (convert_list_to_string(list));
}

char	*expand_parameter(char *str, int quote, t_vlst *env)
{
	int	len;

	len = parameter_size(str);
	if (ft_strncmp(str, "$ ", 2) == 0)
	{
		if (!quote)
			return (ft_strdup("$ "));
		else
			return (ft_strdup("$"));
	}
	else if (ft_strncmp(str, "$", 2) == 0)
		return (ft_strdup("$"));
	else if (quote == DOUBLE_QUOTE && ft_strncmp(str, "$\"", 2) == 0)
		return (ft_strdup("$"));
	else if (ft_strncmp(str, "$", len) == 0)
		return (ft_strdup(""));
	else if (ft_strncmp(str, "$?", len) == 0)
		return (ft_itoa(env->last_status));
	else
		return (expand_variable(str, env));
}

char	*expand_variable(char *str, t_vlst *env)
{
	char	*expand;
	t_node	*node;

	expand = get_parameter_name(str);
	if (!is_valid_name(expand))
	{
		free(expand);
		error_message2(1, str, "bad substitution");
		return (NULL);
	}
	node = find_node_by_content(env->list, expand, find_env_var);
	free(expand);
	if (!node)
		return (ft_strdup(""));
	return (ft_strdup((((t_var *)node->content)->val)));
}

static int	parameter_size(char *str)
{
	int		i;

	i = 0;
	if (str[i++] != '$')
		return (0);
	if (ft_isquote(str[i]) || !str[i])
		return (i);
	if (str[i] == '{')
	{
		while (str[i] && str[i] != '}')
			++i;
		if (str[i++] != '}')
			return (i);
	}
	else if (str[i] == '?')
		++i;
	else
		while (str[i] && ft_isalnum(str[i]))
			++i;
	return (i);
}

static char	*get_parameter_name(char *parameter)
{
	char	*name;
	int		i;
	t_bool	braces;

	if (!parameter)
		return (NULL);
	if (*parameter == '$')
		++parameter;
	braces = FALSE;
	if (*parameter == '{')
	{
		braces = TRUE;
		++parameter;
	}
	i = 0;
	while (parameter[i]
		&& ((!braces && ft_isalnum(parameter[i]))
			|| (braces && parameter[i] != '}')))
		++i;
	name = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(name, parameter, i + 1);
	return (name);
}
