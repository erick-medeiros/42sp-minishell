NAME = debug.a

CFLAGS = -I../../libft -I../../include -g

HEADER = debug.h
SRC = debug.c
SRC += debug_tree.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@clang-format -i $<
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(HEADER) $(OBJ)
	ar -rcs $(NAME) $(OBJ)

fclean:
	rm -fr $(OBJ)

re: fclean all

.PHONY: all clean fclean re