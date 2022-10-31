NAME = debug.a

HEADER = debug.h
SRC = debug.c
SRC += debug_tree.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@clang-format -i $<
	cc -g -I../include -I../libft -c $< -o $@

$(NAME): $(HEADER) $(OBJ)
	@ar -rcs $(NAME) $(OBJ)

fclean:
	@rm -fr $(OBJ)