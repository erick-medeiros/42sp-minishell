NAME = minishell

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Ilibft -g
LIBFLAGS = -Llibft -lft -lreadline
CC = cc
RM = rm -fr

LIBFT_DIR = libft/
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/

LIBFT = $(LIBFT_DIR)/libft.a

FILES = main.c
FILES += $(addprefix builtins/, cd.c echo.c env.c exit.c export.c pwd.c unset.c)
FILES += $(addprefix executor/, command.c converter.c errors.c executor.c)
FILES += $(addprefix executor/, expansion.c pipeline.c redirect.c search.c)
FILES += $(addprefix expander/, env_conv.c env_utils.c expander_utils.c parameter.c quotes.c)
FILES += $(addprefix lexer/, append.c brace.c continue.c double_quote.c heredoc.c input.c lexer.c)
FILES += $(addprefix lexer/, lexer_utils.c output.c pipe.c single_quote.c skip.c word.c)
FILES += $(addprefix parser/, build_tree.c handle_tokens.c heredoc.c incomplete.c)
FILES += $(addprefix parser/, parser.c parser_utils.c postfix.c type.c validation.c)
FILES += $(addprefix prompt/, minishell.c prompt.c prompt_utils.c signal.c)
FILES += $(addprefix utils/, cleanup.c command.c error.c list.c)
FILES += $(addprefix utils/, queue.c quicksort.c stack.c tree.c utils.c vars.c)

SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

FILES_INC = builtins.h executor.h expander.h lexer.h minishell.h parser.h structs.h
HEADERS = $(addprefix $(INC_DIR), $(FILES_INC))
REQUIRED_DIRS = $(sort $(dir $(OBJ)))

NAME_BONUS = minishell_bonus
SRC_DIR_BONUS = bonus/src/
OBJ_DIR_BONUS = bonus/obj/
INC_DIR_BONUS = bonus/include/

FILES_BONUS = main_bonus.c
FILES_BONUS += $(addprefix builtins/, cd_bonus.c echo_bonus.c env_bonus.c exit_bonus.c)
FILES_BONUS += $(addprefix builtins/, export_bonus.c pwd_bonus.c unset_bonus.c)
FILES_BONUS += $(addprefix executor/, command_bonus.c converter_bonus.c errors_bonus.c executor_bonus.c)
FILES_BONUS += $(addprefix executor/, expansion_bonus.c pipeline_bonus.c redirect_bonus.c search_bonus.c)
FILES_BONUS += $(addprefix expander/, env_conv_bonus.c env_utils_bonus.c expander_utils_bonus.c )
FILES_BONUS += $(addprefix expander/, filename_bonus.c parameter_bonus.c quotes_bonus.c)
FILES_BONUS += $(addprefix lexer/, ampersand_bonus.c and_bonus.c or_bonus.c append_bonus.c brace_bonus.c)
FILES_BONUS += $(addprefix lexer/, continue_bonus.c double_quote_bonus.c heredoc_bonus.c input_bonus.c)
FILES_BONUS += $(addprefix lexer/, lexer_bonus.c lexer_utils_bonus.c output_bonus.c pipe_bonus.c)
FILES_BONUS += $(addprefix lexer/, single_quote_bonus.c skip_bonus.c word_bonus.c parenthesis_bonus.c)
FILES_BONUS += $(addprefix parser/, build_tree_bonus.c handle_tokens_bonus.c heredoc_bonus.c incomplete_bonus.c)
FILES_BONUS += $(addprefix parser/, parser_bonus.c parser_utils_bonus.c postfix_bonus.c type_bonus.c validation_bonus.c)
FILES_BONUS += $(addprefix prompt/, minishell_bonus.c prompt_bonus.c prompt_utils_bonus.c signal_bonus.c)
FILES_BONUS += $(addprefix utils/, cleanup_bonus.c command_bonus.c error_bonus.c list_bonus.c queue_bonus.c)
FILES_BONUS += $(addprefix utils/, quicksort_bonus.c stack_bonus.c tree_bonus.c utils_bonus.c vars_bonus.c)

SRC_BONUS = $(addprefix $(SRC_DIR_BONUS), $(FILES_BONUS))
OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS), $(FILES_BONUS:.c=.o))

FILES_INC_BONUS = builtins_bonus.h executor_bonus.h expander_bonus.h lexer_bonus.h
FILES_INC_BONUS += minishell_bonus.h parser_bonus.h structs_bonus.h
HEADERS_BONUS = $(addprefix $(INC_DIR_BONUS), $(FILES_INC_BONUS))
REQUIRED_DIRS_BONUS = $(sort $(dir $(OBJ_BONUS)))

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

$(NAME): $(REQUIRED_DIRS) $(OBJ) | libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

bonus: $(NAME_BONUS)

$(REQUIRED_DIRS_BONUS):
	@mkdir -p $@

$(NAME_BONUS): $(REQUIRED_DIRS_BONUS) $(OBJ_BONUS) | libft
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFLAGS)

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c $(HEADERS_BONUS)
	$(CC) $(CFLAGS) -I$(INC_DIR_BONUS) -c $< -o $@

libft:
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C $(LIBFT_DIR) nclean

re: fclean all

rebonus: fclean bonus

install:
	sudo apt install libreadline-dev clang-format bear
	bear -- make re

norm:
	@clear
	@echo "norminette include/ libft/ src/ bonus/ | grep Error"
	@norminette include/ libft/ src/ bonus/ | grep Error || true

leaks:
	valgrind -q --leak-check=full --show-leak-kinds=all --trace-children=yes \
	--suppressions=./tests/readline.supp --track-fds=yes --track-origins=yes \
	./minishell

b_leaks:
	valgrind -q --leak-check=full --show-leak-kinds=all --trace-children=yes \
	--suppressions=./tests/readline.supp --track-fds=yes --track-origins=yes \
	./minishell_bonus

compile_tests: re
	make re -C tests/unit/

unit_tests:
	./tests/unit/run_test.out

.PHONY: all bonus b_leaks clean compile_tests fclean install libft norm leaks re unit_tests
