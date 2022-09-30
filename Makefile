NAME = minishell

INC_DIR = include/
OBJ_DIR = obj/
SRC_DIR = src/
REQUIRED_DIRS = obj/ obj/libft/ obj/prompt/

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I$(INC_DIR) -g
LIBFLAGS = -lreadline
CC = cc
RM = rm -fr

FILES = main.c
FILES += libft/ft_strncmp.c
FILES += libft/ft_math.c
FILES += libft/ft_strlen.c
FILES += prompt/prompt.c
FILES += prompt/here_doc.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(REQUIRED_DIRS) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

install:
	sudo apt-get install libreadline-dev

norm:
	@clear
	@norminette src/* include/* | grep Error || true

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=./tests/readline.supp ./minishell

.PHONY: all clean fclean re install
