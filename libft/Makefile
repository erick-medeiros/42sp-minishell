NAME = libft.a

CFLAGS = -Wall -Wextra -Werror
CC = cc
LIB = ar -rcs
RM = rm -fr

HEADER = libft.h

SRC = ft_atoi.c ft_isalnum.c ft_isalpha.c
SRC += ft_isdigit.c ft_isquote.c ft_isspace.c
SRC += ft_itoa.c ft_math.c ft_split.c
SRC += ft_strappend.c ft_strchr.c ft_strcmp.c
SRC += ft_strdup.c ft_strjoin.c ft_strlcpy.c
SRC += ft_strlen.c ft_strncasecmp.c ft_strncmp.c
SRC += ft_strnstr.c ft_strrchr.c ft_substr.c

OBJ = $(addprefix obj/, $(SRC:.c=.o))

all: $(NAME)

obj:
	mkdir -p obj

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): obj $(OBJ) $(HEADER)
	$(LIB) $(NAME) $(OBJ)

clean:
	$(RM) obj *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
