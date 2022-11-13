/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:14:41 by eandre-f          #+#    #+#             */
/*   Updated: 2022/11/12 23:43:34 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "structs.h"
#include "expander.h"

int	find_env_var(void *str, void *var)
{
	if (command_is_equal(str, ((t_var *)var)->name))
		return (0);
	return (1);
}

int	concat_expanded(char **str, int start, char *str_in, char *str_out)
{
	char	*next;
	char	*previous;
	char	*concat;
	int		len;

	previous = *str;
	previous[start] = '\0';
	next = &previous[start + ft_strlen(str_out)];
	concat = ft_strjoin(previous, str_in);
	len = ft_strlen(concat);
	*str = ft_strjoin(concat, next);
	free(concat);
	free(previous);
	free(str_in);
	free(str_out);
	return (len);
}

char	*get_parameter_expansion(char *str)
{
	char	*param;
	int		i;

	i = 0;
	if (str[i++] != '$')
		return (NULL);
	if (str[i] == '{')
	{
		while (str[i] && str[i] != '}')
			++i;
		if (str[i++] != '}')
			return (NULL);
	}
	else if (!ft_isalnum(str[i]))
		++i;
	else
	{
		while (str[i] && ft_isalnum(str[i]) && str[i] != ' ')
			++i;
	}
	param = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(param, str, i + 1);
	return (param);
}

char	*get_parameter(char *param_expand)
{
	char	*parameter;
	int		i;
	t_bool	braces;

	if (!param_expand)
		return (NULL);
	if (*param_expand == '$')
		++param_expand;
	braces = FALSE;
	if (*param_expand == '{')
	{
		braces = TRUE;
		++param_expand;
	}
	i = 0;
	if (ft_isalnum(param_expand[i]))
		while (param_expand[i] && ft_isalnum(param_expand[i]))
			++i;
	else if (param_expand[0] != ' ' || (braces && param_expand[0] != '}'))
		i = 1;
	parameter = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(parameter, param_expand, i + 1);
	return (parameter);
}