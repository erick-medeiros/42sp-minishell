NAME = minishell

INC_DIR = include/
OBJ_DIR = obj/
SRC_DIR = src/
REQUIRED_DIRS = obj/ obj/libft/ obj/prompt/ obj/list/ obj/builtins/

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I$(INC_DIR)
LIBFLAGS = -lreadline
DEBUGFLAGS = -g
CC = cc
RM = rm -fr

FILES = main.c
FILES += libft/ft_math.c
FILES += libft/ft_split.c
FILES += libft/ft_strchr.c
FILES += libft/ft_strcmp.c
FILES += libft/ft_strdup.c
FILES += libft/ft_strjoin.c
FILES += libft/ft_strlcpy.c
FILES += libft/ft_strlen.c
FILES += libft/ft_strncmp.c
FILES += libft/ft_substr.c
FILES += list/cleanup.c
FILES += list/env_conv.c
FILES += list/env_utils.c
FILES += list/list.c
FILES += prompt/ends_in_pipe.c
FILES += prompt/here_doc.c
FILES += prompt/prompt.c
FILES += builtins/builtins.c
FILES += builtins/cd.c
FILES += builtins/echo.c
FILES += builtins/env.c
FILES += builtins/exit.c
FILES += builtins/export.c
FILES += builtins/pwd.c
FILES += builtins/unset.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

$(NAME): $(REQUIRED_DIRS) $(OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS)

clean:
	$(RM) $(OBJ_DIR)*

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

compile_tests: re
	make re -C tests/unit/

unit_tests:
	./tests/unit/run_test.out

.PHONY: all clean fclean re install norm leaks compile_tests unit_tests
