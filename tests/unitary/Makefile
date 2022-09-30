NAME = run_test.out

MINISHELL_DIR = ../../
MIN_SRC_DIR = $(MINISHELL_DIR)src/
MIN_OBJ_DIR = $(MINISHELL_DIR)obj/
MIN_INC_DIR = $(MINISHELL_DIR)include/
MINISHELL = $(MINISHELL_DIR)minishell

CFLAGS = -IUnity -I$(MIN_INC_DIR)
LIBFLAGS = -lreadline

FILES = main.c
FILES += Unity/unity.c

OBJS = $(FILES:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MINISHELL) $(OBJS)
	gcc $(CFLAGS) $(OBJS) \
	$(filter-out $(MIN_OBJ_DIR)main.o, $(wildcard $(MIN_OBJ_DIR)*/*.o $(MIN_OBJ_DIR)*.o)) \
	-o $(NAME) $(LIBFLAGS)

$(MINISHELL):
	make -C $(MINISHELL_DIR)

clean:
	rm -fr Unity/unity.o
	rm -fr main.o

fclean:	clean
	rm -fr $(NAME)

re:	fclean all

.PHONY: all clean fclean re minishell