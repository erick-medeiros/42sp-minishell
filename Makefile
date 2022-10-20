NAME = minishell

INC_DIR = include/
OBJ_DIR = obj/
SRC_DIR = src/

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I$(INC_DIR)
LIBFLAGS = -lreadline
DEBUGFLAGS = -Isrc/debug/ -g
CC = cc
RM = rm -fr

FILES = main.c
FILES += debug/debug.c
FILES += libft/ft_isspace.c
FILES += libft/ft_math.c
FILES += libft/ft_split.c
FILES += libft/ft_split_cmd.c
FILES += libft/ft_strchr.c
FILES += libft/ft_strcmp.c
FILES += libft/ft_strdup.c
FILES += libft/ft_strjoin.c
FILES += libft/ft_strlcpy.c
FILES += libft/ft_strlen.c
FILES += libft/ft_strncmp.c
FILES += libft/ft_strrchr.c
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
FILES += lexer/lexer.c
FILES += lexer/append.c
FILES += lexer/double_quote.c
FILES += lexer/end.c
FILES += lexer/input.c
FILES += lexer/output.c
FILES += lexer/pipe.c
FILES += lexer/single_quote.c
FILES += lexer/space.c
FILES += lexer/start.c
FILES += lexer/word.c
FILES += parser/parser.c
FILES += expansor/expansor.c
FILES += executor/executor.c
FILES += executor/pathname.c
FILES += free/free.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

MODULES = libft/ prompt/ list/ builtins/ lexer/
MODULES += parser/ expansor/ executor/ free/ debug/

REQUIRED_DIRS = $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(MODULES))

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
