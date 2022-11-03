/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachado <gmachado@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 23:11:00 by gmachado          #+#    #+#             */
/*   Updated: 2022/11/03 00:03:21 by gmachado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	(void)ms;
	*dst = ft_strdup(src);
	return (OK);
}
