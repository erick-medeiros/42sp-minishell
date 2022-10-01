/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eandre-f <eandre-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:27:27 by eandre-f          #+#    #+#             */
/*   Updated: 2022/10/01 12:48:36 by eandre-f         ###   ########.fr       */
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

# define PROMPT_STRING "minishell> "
# define HEREDOC_STRING "here_doc> "
# define ENDSINPIPE_STRING "> "

void	miniprompt(void);
int		command_is_equal(char *cmd, char *str);
int		command_ends_with(char *cmd, char c);
char	*get_content_fd(int fd);
int		here_doc(char	*limiter);
int		ends_in_pipe(void);

#endif
