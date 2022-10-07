NAME = run_test.out

MINISHELL_DIR = ../../
MIN_SRC_DIR = $(MINISHELL_DIR)src/
MIN_OBJ_DIR = $(MINISHELL_DIR)obj/
MIN_INC_DIR = $(MINISHELL_DIR)include/
MINISHELL = $(MINISHELL_DIR)minishell
OBJ_DIR = obj/
REQUIRED_DIRS = obj/ obj/Unity/

CFLAGS = -Wall -Wextra -Werror
CFLAGS += -IUnity -I$(MIN_INC_DIR) -g
LIBFLAGS = -lreadline
RM = rm -fr

FILES = main.c
FILES += Unity/unity.c
FILES += prompt.c
FILES += list_test.c
FILES += builtins_test.c

OBJS = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(REQUIRED_DIRS) $(MINISHELL) $(OBJS)
	gcc $(CFLAGS) $(OBJS) \
	$(filter-out $(MIN_OBJ_DIR)main.o, $(wildcard $(MIN_OBJ_DIR)*/*.o $(MIN_OBJ_DIR)*.o)) \
	-o $(NAME) $(LIBFLAGS)

$(MINISHELL):
	make -C $(MINISHELL_DIR)

reminishell:
	make re -C $(MINISHELL_DIR)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re reminishell