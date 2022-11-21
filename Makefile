NAME = minishell
NAME_BONUS = minishell_bonus

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
FILES += $(addprefix lexer/, append.c brace.c continue.c double_quote.c heredoc.c input.c lexer.c)
FILES += $(addprefix lexer/, lexer_utils.c output.c pipe.c single_quote.c skip.c word.c)
FILES += $(addprefix parser/, build_tree.c handle_tokens.c parser.c parser_utils.c postfix.c)
FILES += $(addprefix prompt/, here_doc.c prompt.c prompt_utils.c signal.c)
FILES += $(addprefix utils/, cleanup.c command.c error.c free.c list.c minishell.c)
FILES += $(addprefix utils/, queue.c quicksort.c stack.c tree.c utils.c vars.c)

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

FILES_INC = builtins.h executor.h expander.h lexer.h minishell.h parser.h structs.h
HEADERS = $(addprefix $(INC_DIR), $(FILES_INC))
REQUIRED_DIRS = $(sort $(dir $(OBJ)))

SRC_DIR_BONUS = bonus/src/
OBJ_DIR_BONUS = bonus/obj/
INC_DIR_BONUS = bonus/include/

FILES_BONUS = main_bonus.c
FILES_BONUS += $(addprefix builtins/, cd_bonus.c echo_bonus.c env_bonus.c exit_bonus.c export_bonus.c pwd_bonus.c unset_bonus.c)
FILES_BONUS += $(addprefix executor/, command_bonus.c executor_bonus.c expansion_bonus.c redirect_bonus.c)
FILES_BONUS += $(addprefix executor/, search_bonus.c errors_bonus.c)
FILES_BONUS += $(addprefix expander/, env_conv_bonus.c env_utils_bonus.c expander_utils_bonus.c)
FILES_BONUS += $(addprefix expander/, filename_bonus.c parameter_bonus.c quotes_bonus.c)
FILES_BONUS += $(addprefix lexer/, ampersand_bonus.c and_bonus.c append_bonus.c brace_bonus.c continue_bonus.c)
FILES_BONUS += $(addprefix lexer/, double_quote_bonus.c heredoc_bonus.c input_bonus.c lexer_bonus.c lexer_utils_bonus.c)
FILES_BONUS += $(addprefix lexer/, or_bonus.c output_bonus.c pipe_bonus.c single_quote_bonus.c skip_bonus.c word_bonus.c)
FILES_BONUS += $(addprefix parser/, build_tree_bonus.c handle_tokens_bonus.c parser_bonus.c parser_utils_bonus.c postfix_bonus.c)
FILES_BONUS += $(addprefix prompt/, here_doc_bonus.c prompt_bonus.c prompt_utils_bonus.c signal_bonus.c)
FILES_BONUS += $(addprefix utils/, cleanup_bonus.c command_bonus.c error_bonus.c free_bonus.c list_bonus.c minishell_bonus.c)
FILES_BONUS += $(addprefix utils/, queue_bonus.c quicksort_bonus.c stack_bonus.c tree_bonus.c utils_bonus.c vars_bonus.c)

SRC_BONUS = $(addprefix $(SRC_DIR_BONUS), $(FILES_BONUS))
OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS), $(FILES_BONUS:.c=.o))

FILES_INC_BONUS = builtins_bonus.h executor_bonus.h expander_bonus.h lexer_bonus.h minishell_bonus.h parser_bonus.h structs_bonus.h
HEADERS_BONUS = $(addprefix $(INC_DIR_BONUS), $(FILES_INC_BONUS))
REQUIRED_DIRS_BONUS = $(sort $(dir $(OBJ_BONUS)))

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

$(REQUIRED_DIRS_BONUS):
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

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(REQUIRED_DIRS_BONUS) $(HEADERS_BONUS) $(OBJ_BONUS) | libft libdebug
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBDEBUG) $(LIBFLAGS)

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
