NAME = debug.a

SRC = debug.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@clang-format -i $<
	@cc -I../include -I../libft -c $< -o $@

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)
	@rm -fr $(OBJ)