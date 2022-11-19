NAME = libft.a

CFLAGS = -Wall -Wextra -Werror
CC = cc
LIB = ar -rcs
RM = rm -fr

HEADER = libft.h

SRC = ft_atoi.c ft_checked_atoll.c ft_isalnum.c
SRC += ft_isalpha.c ft_isdigit.c ft_isquote.c
SRC += ft_isspace.c ft_itoa.c ft_math.c ft_put.c
SRC += ft_split.c ft_strappend.c ft_strchr.c
SRC += ft_strcmp.c ft_strdup.c ft_strjoin.c
SRC += ft_strlcpy.c ft_strlen.c ft_strncmp.c
SRC += ft_strndup.c ft_strnstr.c ft_strrchr.c
SRC += ft_substr.c get_next_line.c

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
