NAME = libft.a

CFLAGS = -Wall -Wextra -Werror
CC = cc
LIB = ar -rcs
RM = rm -fr

HEADER = libft.h

SRC = ft_itoa.c ft_isalpha.c ft_isdigit.c ft_isspace.c
SRC += ft_math.c ft_split.c ft_strappend.c
SRC += ft_strchr.c ft_strcmp.c ft_strdup.c
SRC += ft_strjoin.c ft_strlcpy.c ft_strlen.c
SRC += ft_strncmp.c ft_strrchr.c ft_substr.c

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
