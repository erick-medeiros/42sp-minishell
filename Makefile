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

FILES = main.c
FILES += $(addprefix builtins/, cd.c echo.c env.c exit.c export.c pwd.c unset.c)
FILES += $(addprefix executor/, executor.c pipeline.c subshell.c)
FILES += $(addprefix expander/, env_conv.c env_utils.c expander.c pathname.c quotes.c)
FILES += $(addprefix lexer/, append.c continue.c double_quote.c heredoc.c input.c lexer.c)
FILES += $(addprefix lexer/, lexer_utils.c output.c pipe.c single_quote.c skip.c word.c)
FILES += $(addprefix parser/, build_tree.c builtins.c expand.c handle_tokens.c parser.c parser_utils.c postfix.c)
FILES += $(addprefix prompt/, here_doc.c prompt.c prompt_utils.c signal.c)
FILES += $(addprefix utils/, cleanup.c command.c error.c free.c list.c minishell.c queue.c tree.c utils.c)

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

FILES_INC = builtins.h executor.h expander.h lexer.h minishell.h parser.h structs.h
HEADERS = $(addprefix include/, $(FILES_INC))

REQUIRED_DIRS = $(sort $(dir $(OBJ)))

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
	$(RM) $(NAME) $(LIBFT) $(LIBDEBUG)

re: fclean all

install:
	sudo apt install libreadline-dev clang-format bear
	bear -- make re

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
