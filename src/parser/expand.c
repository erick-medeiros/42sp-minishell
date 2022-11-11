/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 23:11:00 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/11 17:42:02 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

// TODO: implement expansion of filename word token values
int	expand_filename(char *src, char **dst, t_minishell *ms)
{
	(void)ms;
	*dst = ft_strdup(src);
	return (OK);
}

// TODO: implement expansion of non-filename word token values
int	expand_vars(char *src, char **dst, t_minishell *ms)
{
	*dst = expander_vars(&ms->env_list, src);
	return (OK);
}
