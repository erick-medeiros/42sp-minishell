NAME = minishell

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Ilibft
LIBFLAGS = -Llibft -lft -lreadline
DEBUGFLAGS = -Idebug -g
CC = cc
RM = rm -fr

LIBFT_DIR = libft/
LIBFT = libft/libft.a
LIBDEBUG = debug/debug.a

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/

FILES = main.c
FILES += $(addprefix builtins/, cd.c echo.c env.c exit.c export.c pwd.c unset.c)
FILES += $(addprefix executor/, command.c executor.c expansion.c redirect.c)
FILES += $(addprefix executor/, search.c errors.c)
FILES += $(addprefix expander/, env_conv.c env_utils.c expander_utils.c filename.c parameter.c quotes.c)
FILES += $(addprefix lexer/, ampersand.c and.c or.c append.c brace.c continue.c double_quote.c heredoc.c)
FILES += $(addprefix lexer/, input.c lexer.c lexer_utils.c output.c pipe.c single_quote.c skip.c word.c)
FILES += $(addprefix parser/, build_tree.c handle_tokens.c parser.c parser_utils.c postfix.c)
FILES += $(addprefix prompt/, here_doc.c prompt.c prompt_utils.c signal.c)
FILES += $(addprefix utils/, cleanup.c command.c error.c free.c list.c minishell.c)
FILES += $(addprefix utils/, queue.c quicksort.c stack.c tree.c utils.c vars.c)

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

FILES_INC = builtins.h executor.h expander.h lexer.h minishell.h parser.h structs.h
HEADERS = $(addprefix $(INC_DIR), $(FILES_INC))
REQUIRED_DIRS = $(sort $(dir $(OBJ)))

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

$(OBJ_DIR_BONUS)%_bonus.o: $(SRC_DIR_BONUS)%_bonus.c
	$(CC) $(CFLAGS) -I$(INC_DIR_BONUS) $(DEBUGFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) $(DEBUGFLAGS) -c $< -o $@

libft:
	make -C $(LIBFT_DIR)

libdebug:
	make -C debug

$(NAME): $(REQUIRED_DIRS) $(HEADERS) $(OBJ) | libft libdebug
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(OBJ) $(LIBDEBUG) $(LIBFLAGS)

clean:
	$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS) $(LIBFT) $(LIBDEBUG)

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

.PHONY: all clean compile_tests fclean install libdebug libft norm leaks re unit_tests
