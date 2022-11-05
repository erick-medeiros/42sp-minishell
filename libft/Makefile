NAME = libft.a

CFLAGS = -Wall -Wextra -Werror
CC = cc
LIB = ar -rcs
RM = rm -fr

HEADER = libft.h

SRC = ft_math.c ft_split.c ft_isspace.c
SRC += ft_strchr.c ft_strrchr.c ft_strcmp.c
SRC += ft_strdup.c ft_strjoin.c ft_strlcpy.c
SRC += ft_strlen.c ft_strncmp.c ft_substr.c
SRC += ft_strappend.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	$(LIB) $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
