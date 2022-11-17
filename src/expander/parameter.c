/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:08:48 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/17 18:05:35 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "builtins.h"
#include "minishell.h"

static int	parameter_size(char *str);
static char	*get_parameter_name(char *parameter);

char	*parameter_expansion(char *src, t_vlst *env_list, int status)
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
		if (ft_isquote(src[i]) && (!quote || src[i] == quote))
			quote = update_quote(src[i], quote);
		if (src[i] == '$' && (!quote || quote == DOUBLE_QUOTE))
		{
			add_node(&list, ft_strndup(&src[start], i - start));
			add_node(&list, expand_parameter(&src[i], env_list, status));
			i += parameter_size(&src[i]);
			start = i;
		}
		else
			++i;
	}
	add_node(&list, ft_strdup(&src[start]));
	return (convert_list_to_string(list));
}

char	*expand_parameter(char *str, t_vlst *env_list, int status)
{
	int	len;

	len = parameter_size(str);
	if (ft_strncmp(str, "$", len) == 0)
		return (ft_strdup(""));
	else if (ft_strncmp(str, "$?", len) == 0)
		return (ft_itoa(status));
	else
		return (expand_variable(env_list, str));
}

char	*expand_variable(t_vlst *env_list, char *str)
{
	char	*expand;
	t_node	*node;

	expand = get_parameter_name(str);
	if (!is_valid_name(expand))
	{
		free(expand);
		ft_putstr_fd(str, STDERR);
		ft_putendl_fd(": bad substitution", STDERR);
		return (NULL);
	}
	node = find_node_by_content(env_list->list, expand, find_env_var);
	free(expand);
	if (!node)
		return (NULL);
	return (ft_strdup((((t_var *)node->content)->val)));
}

static int	parameter_size(char *str)
{
	int		i;

	i = 0;
	if (str[i++] != '$')
		return (0);
	if (ft_isquote(str[i]))
		return (i);
	if (str[i] == '{')
	{
		while (str[i] && str[i] != '}')
			++i;
		if (str[i++] != '}')
			return (i);
	}
	else if (!ft_isalnum(str[i]) && str[i] != ' ')
		++i;
	else
		while (str[i] && ft_isalnum(str[i]) && str[i] != ' ')
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
	if (ft_isalnum(parameter[i]))
		while (parameter[i] && ft_isalnum(parameter[i]))
			++i;
	else if (parameter[0] != ' ' || (braces && parameter[0] != '}'))
		i = 1;
	name = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(name, parameter, i + 1);
	return (name);
}