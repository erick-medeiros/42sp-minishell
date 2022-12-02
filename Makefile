NAME = minishell

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Ilibft -g
LIBFLAGS = -Llibft -lft -lreadline
CC = cc
RM = rm -fr

LIBFT_DIR = libft/
LIBFT = libft/libft.a

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/

FILES = main.c
FILES += $(addprefix builtins/, cd.c echo.c env.c exit.c export.c pwd.c unset.c)
FILES += $(addprefix executor/, command.c executor.c expansion.c redirect.c)
FILES += $(addprefix executor/, search.c errors.c pipeline.c)
FILES += $(addprefix expander/, env_conv.c env_utils.c expander_utils.c filename.c parameter.c quotes.c)
FILES += $(addprefix lexer/, ampersand.c and.c or.c append.c brace.c continue.c double_quote.c heredoc.c)
FILES += $(addprefix lexer/, input.c lexer.c lexer_utils.c output.c pipe.c single_quote.c skip.c word.c)
FILES += $(addprefix lexer/, parenthesis.c)
FILES += $(addprefix parser/, build_tree.c handle_tokens.c heredoc.c parser.c)
FILES += $(addprefix parser/, parser_utils.c postfix.c type.c validation.c)
FILES += $(addprefix prompt/, prompt.c prompt_utils.c signal.c)
FILES += $(addprefix utils/, cleanup.c command.c error.c list.c minishell.c)
FILES += $(addprefix utils/, queue.c quicksort.c stack.c tree.c utils.c vars.c)

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

FILES_INC = builtins.h executor.h expander.h lexer.h minishell.h parser.h structs.h
HEADERS = $(addprefix $(INC_DIR), $(FILES_INC))
REQUIRED_DIRS = $(sort $(dir $(OBJ)))

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

libft:
	make -C $(LIBFT_DIR)

$(NAME): $(REQUIRED_DIRS) $(HEADERS) $(OBJ) | libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS)

clean:
	$(RM) $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) nclean


re: fclean all

install:
	sudo apt install libreadline-dev clang-format bear
	bear -- make re

norm:
	@clear
	@echo "norminette include/ libft/ src/ | grep Error"
	@norminette include/ libft/ src/ | grep Error || true

leaks:
	valgrind --leak-check=full --show-leak-kinds=all \
	--suppressions=./tests/readline.supp --track-fds=yes --track-origins=yes \
	./minishell

compile_tests: re
	make re -C tests/unit/

unit_tests:
	./tests/unit/run_test.out

.PHONY: all clean compile_tests fclean install libft norm leaks re unit_tests
