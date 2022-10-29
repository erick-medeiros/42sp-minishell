NAME = minishell

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Ilibft -Iinclude
LIBFLAGS = -Llibft -lft -lreadline
DEBUGFLAGS = -Idebug -g
CC = cc
RM = rm -fr

LIBFT_DIR = libft/
LIBFT = libft/libft.a
LIBDEBUG = debug/debug.a
SRC_DIR = src/
OBJ_DIR = obj/
MODULES = prompt/ builtins/ lexer/ parser/ expansor/ executor/ utils/

FILES = main.c
FILES += utils/cleanup.c utils/list.c utils/free.c utils/error.c
FILES += utils/command.c utils/minishell.c utils/utils.c
FILES += prompt/ends_in_pipe.c prompt/here_doc.c prompt/prompt.c
FILES += lexer/append.c lexer/double_quote.c lexer/heredoc.c lexer/input.c lexer/lexer.c lexer/lexer_utils.c
FILES += lexer/output.c lexer/pipe.c lexer/single_quote.c lexer/skip.c lexer/word.c
FILES += expansor/env_conv.c expansor/env_utils.c expansor/pathname.c
FILES += parser/parser.c parser/builtins.c
FILES += builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c
FILES += builtins/export.c builtins/pwd.c builtins/unset.c
FILES += executor/executor.c executor/pipeline.c executor/subshell.c

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

FILES_INC = builtins.h executor.h expansor.h lexer.h minishell.h parser.h structs.h
HEADERS = $(addprefix include/, $(FILES_INC))

REQUIRED_DIRS = $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(MODULES))

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBDEBUG):
	make -C debug

$(NAME): $(REQUIRED_DIRS) $(HEADERS) $(OBJ) $(LIBFT) $(LIBDEBUG)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(OBJ) $(LIBDEBUG) $(LIBFLAGS)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

install:
	sudo apt install libreadline-dev clang-format

norm:
	@clear
	@echo "norminette include/ libft/ src/ | grep Error"
	@norminette include/ libft/ src/ | grep Error || true

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=./tests/readline.supp ./minishell

compile_tests: re
	make re -C tests/unit/

unit_tests:
	./tests/unit/run_test.out

.PHONY: all clean fclean re install norm leaks compile_tests unit_tests
