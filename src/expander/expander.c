/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:08:48 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/15 21:20:41 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "minishell.h"
#include "expander.h"

static int	bad_substitution(char **dst, char *src);

int	expander(char *src, char **dst, t_minishell *ms)
{
	char	*expanded;
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
			expanded = expand_parameter(&src[i], ms);
			if (!expanded)
				return (bad_substitution(dst, src));
			i = concat_expanded(&src, i, expanded);
		}
		else
			++i;
	}
	*dst = remove_quote(src);
	free(src);
	return (OK);
}

char	*expand_parameter(char *str, t_minishell *ms)
{
	if (ft_streq(str, "$"))
		return (ft_strdup(""));
	else if (ft_streq(str, "$?"))
		return (ft_strdup(ft_itoa(ms->exit_status)));
	else
		return (expand_variable(&ms->env_list, str));
}

char	*expand_variable(t_vlst *env_list, char *str)
{
	char	*expand;
	t_node	*node;

	expand = get_parameter(str);
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

static int	bad_substitution(char **dst, char *src)
{
	free(src);
	if (dst)
		*dst = NULL;
	return (OK);
}
