/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:07:14 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/13 15:59:56 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_max(int number1, int number2);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_split_count(char const *s, char c);
char	**ft_split(char const *s, char c);
size_t	ft_split_cmd_count(char const *s, char c);
char	**ft_split_cmd(char const *s, char c);

#endif