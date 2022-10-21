NAME = run_test.out

MINISHELL_DIR = ../../
MIN_SRC_DIR = $(MINISHELL_DIR)src/
MIN_OBJ_DIR = $(MINISHELL_DIR)obj/
MIN_INC_DIR = $(MINISHELL_DIR)include/
MINISHELL = $(MINISHELL_DIR)minishell

LIBFT_DIR = $(MINISHELL_DIR)libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBDEBUG = $(MINISHELL_DIR)debug/debug.a

MIN_SRC_FILES=$(filter-out $(MIN_SRC_DIR)main.c, $(wildcard $(MIN_SRC_DIR)*/*.c $(MIN_SRC_DIR)*.c))
MIN_OBJ_FILES=$(filter-out $(MIN_OBJ_DIR)main.o, $(wildcard $(MIN_OBJ_DIR)*/*.o $(MIN_OBJ_DIR)*.o))
OBJ_DIR = obj/
REQUIRED_DIRS = obj/ obj/Unity/

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -IUnity -I$(MIN_INC_DIR) -I$(LIBFT_DIR) -g
CFLAGS += -I$(MIN_SRC_DIR)debug -I$(MIN_SRC_DIR)executor/ -I$(MIN_SRC_DIR)parser/
LIBFLAGS = -L$(LIBFT_DIR) -lft -lreadline
RM = rm -fr
FORMAT = clang-format -i

FILES = main_test.c
FILES += Unity/unity.c
FILES += unit_tests_utils.c
FILES += prompt_test.c
FILES += list_test.c
FILES += builtins_test.c
FILES += environment_test.c
FILES += pathname_test.c

OBJS = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: %.c
	$(FORMAT) $<
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(REQUIRED_DIRS) $(OBJS) $(MIN_SRC_FILES) $(MIN_OBJ_FILES) $(LIBDEBUG) $(MINISHELL)
	make -C $(MINISHELL_DIR)
	gcc $(CFLAGS) $(OBJS) \
	$(filter-out $(MIN_OBJ_DIR)main.o, $(wildcard $(MIN_OBJ_DIR)*/*.o $(MIN_OBJ_DIR)*.o)) \
	-o $(NAME) $(LIBDEBUG) $(LIBFLAGS)

reminishell:
	make re -C $(MINISHELL_DIR)
	make re

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

leaks:
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--suppressions=../readline.supp \
		--track-fds=yes \
		--track-origins=yes \
		./$(NAME)

.PHONY: all clean fclean re reminishell leaks
