/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:08:48 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/12 23:43:18 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "expander.h"

int	expander(char *src, char **dst, t_minishell *ms)
{
	char	*expanded;
	char	*param_expand;
	int		i;
	int		quote;

	quote = 0;
	src = ft_strdup(src);
	i = 0;
	while (src[i])
	{
		if (ft_isquote(src[i]) && (!quote || src[i] == quote))
			quote = update_quote(src[i], quote);
		if (src[i] == '$' && (!quote || quote == DOUBLE_QUOTE))
		{
			param_expand = get_parameter_expansion(&src[i]);
			expanded = expand_parameter(&src[i], param_expand, ms);
			i = concat_expanded(&src, i, expanded, param_expand);
		}
		else
			++i;
	}
	*dst = remove_quote(src);
	free(src);
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
