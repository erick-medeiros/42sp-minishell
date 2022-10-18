NAME = minishell

INC_DIR = include/
OBJ_DIR = obj/
SRC_DIR = src/

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I$(INC_DIR) -g
LIBFLAGS = -lreadline
CC = cc
RM = rm -fr

FILES = main.c
FILES += libft/ft_strncmp.c
FILES += libft/ft_math.c
FILES += libft/ft_strlen.c
FILES += libft/ft_strjoin.c
FILES += libft/ft_strdup.c
FILES += libft/ft_strlcpy.c
FILES += libft/ft_substr.c
FILES += libft/ft_split.c
FILES += libft/ft_split_cmd.c
FILES += list/cleanup.c
FILES += list/list.c
FILES += prompt/prompt.c
FILES += prompt/here_doc.c
FILES += prompt/ends_in_pipe.c
FILES += builtins/builtins.c
FILES += builtins/echo.c
FILES += builtins/cd.c
FILES += builtins/pwd.c
FILES += builtins/exit.c
FILES += lexer/lexer.c
FILES += parser/parser.c
FILES += expansor/expansor.c
FILES += executor/executor.c
FILES += free/free.c

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

REQUIRED_DIRS = obj/
REQUIRED_DIRS += obj/libft/
REQUIRED_DIRS += obj/prompt/
REQUIRED_DIRS += obj/list/
REQUIRED_DIRS += obj/builtins/
REQUIRED_DIRS += obj/lexer/
REQUIRED_DIRS += obj/parser/
REQUIRED_DIRS += obj/expansor/
REQUIRED_DIRS += obj/executor/
REQUIRED_DIRS += obj/free/

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

compile_tests: re
	make re -C tests/unit/

unit_tests:
	./tests/unit/run_test.out

.PHONY: all clean fclean re install norm leaks compile_tests unit_tests
