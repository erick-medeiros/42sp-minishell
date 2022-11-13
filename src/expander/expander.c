/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:08:48 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/12 20:57:04 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "expander.h"

int	expander(char *src, char **dst, t_minishell *ms)
{
	char	*expanded;
	char	*param_expand;
	char	*tmp;
	int		i;

	src = ft_strdup(src);
	i = 0;
	while (src[i])
	{
		if (src[i] == '$')
		{
			param_expand = get_parameter_expansion(&src[i]);
			expanded = expand_parameter(&src[i], param_expand, ms);
			i = concat_expanded(&src, i, expanded, param_expand);
			free(expanded);
			free(param_expand);
		}
		else
			++i;
	}
	tmp = src;
	*dst = remove_quote(src);
	free(tmp);
	return (OK);
}

char	*expand_parameter(char *str, char *param_expand, t_minishell *ms)
{
	char	*parameter;
	char	*result;

	parameter = get_parameter(param_expand);
	if (parameter && ft_isalnum(parameter[0]))
		result = expand_variable(&ms->env_list, str);
	else if (parameter && parameter[0] == '?')
		result = ft_strdup("^v^");
	else
		result = ft_strdup("");
	free(parameter);
	return (result);
}

char	*expand_variable(t_vlst *env_list, char *str)
{
	char	*expand;
	t_node	*node;

	expand = get_parameter(str);
	node = find_node_by_content(env_list->list, expand, find_env_var);
	free(expand);
	if (!node)
		return (NULL);
	return (ft_strdup((((t_var *)node->content)->val)));
}
