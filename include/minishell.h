/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:27:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/09/30 11:01:48 by eandre-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>

# include "libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

# define PROMPT_TEXT "minishell> "
# define HERE_DOC_TEXT "here_doc> "

void	miniprompt(void);
int		command_is_equal(char *cmd, char *str);
int		here_doc(char	*limiter);

#endif
