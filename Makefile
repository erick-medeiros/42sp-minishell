NAME = minishell

INC_DIR = include/
OBJ_DIR = obj/
SRC_DIR = src/
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I $(LIBFT_DIR) -I$(INC_DIR)
LIBFLAGS = -L $(LIBFT_DIR) -lft -lreadline
DEBUGFLAGS = -Isrc/debug/ -g
CC = cc
RM = rm -fr

FILES = main.c
FILES += debug/debug.c
FILES += utils/cleanup.c
FILES += utils/list.c
FILES += utils/free.c
FILES += prompt/ends_in_pipe.c
FILES += prompt/here_doc.c
FILES += prompt/prompt.c
FILES += builtins/cd.c
FILES += builtins/echo.c
FILES += builtins/env.c
FILES += builtins/exit.c
FILES += builtins/export.c
FILES += builtins/pwd.c
FILES += builtins/unset.c
FILES += lexer/lexer.c
FILES += parser/parser.c
FILES += expansor/expansor.c
FILES += expansor/env_conv.c
FILES += expansor/env_utils.c
FILES += executor/executor.c
FILES += executor/pathname.c
FILES += executor/child_process.c
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

MODULES = prompt/ builtins/ lexer/
MODULES += parser/ expansor/ executor/ debug/ utils/

REQUIRED_DIRS = $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(MODULES))

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(REQUIRED_DIRS) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS)

clean:
	$(RM) $(OBJ_DIR)*

fclean: clean
	$(RM) $(NAME)

re: fclean all

install:
	sudo apt install libreadline-dev clang-format

norm:
	@clear
	@norminette include/ libft/ src/ | grep Error || true

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=./tests/readline.supp ./minishell

compile_tests: re
	make re -C tests/unit/

unit_tests:
	./tests/unit/run_test.out

.PHONY: all clean fclean re install norm leaks compile_tests unit_tests
