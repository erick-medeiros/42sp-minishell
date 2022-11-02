NAME = run_unity_tests.out

MINISHELL_DIR = ../../
MIN_SRC_DIR = ${MINISHELL_DIR}src/
MIN_OBJ_DIR = ${MINISHELL_DIR}obj/
MIN_INC_DIR = ${MINISHELL_DIR}include/
MINISHELL = ${MINISHELL_DIR}minishell

LIBFT_DIR = ${MINISHELL_DIR}libft/
LIBFT = ${LIBFT_DIR}libft.a
LIBDEBUG = ${MINISHELL_DIR}debug/debug.a
LIBUTILS_DIR = ../lib/
UNITY_OBJ_DIR = ../obj/Unity/
TEST_UTILS_OBJ_DIR = ../obj/test_utils/

MIN_SRC_FILES=${wildcard ${MIN_SRC_DIR}*/*.c}
MIN_OBJ_FILES=${wildcard ${MIN_OBJ_DIR}*/*.o}
OBJ_DIR = obj/

CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=address
CFLAGS += -I${LIBFT_DIR} -I${MIN_INC_DIR} -I${MIN_SRC_DIR}debug -I../lib -I../lib/test_utils -g
LIBFLAGS = -L${LIBFT_DIR} -lft -lreadline
RM = rm -fr
FORMAT = clang-format -i

UNIT_FILES = main_test.c
UNIT_FILES += builtins/builtins_test.c
UNIT_FILES += ${addprefix executor/, executor_test.c pipeline_test.c subshell_test.c}
UNIT_FILES += lexer/lexer_test.c
UNIT_FILES += prompt/prompt_test.c
UNIT_FILES += ${addprefix utils/, environment_test.c list_test.c utils_test.c}
UNIT_FILES += ${addprefix expansor/, pathname_test.c}

OBJS = ${addprefix ${OBJ_DIR}, ${UNIT_FILES:.c=.o}}

REQUIRED_DIRS = ${sort ${dir ${OBJS}}}

all: ${NAME}

run:
	./run_unity_tests.out

${REQUIRED_DIRS}:
	mkdir -p $@

${OBJ_DIR}%.o: %.c
	@${FORMAT} $<
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${REQUIRED_DIRS} ${OBJS} ${LIBDEBUG} ${LIBFT} ${MIN_OBJ_FILES} ${MIN_INC_DIR}*.h ${LIBUTILS_DIR}/Unity/*.h ${LIBUTILS_DIR}/test_utils/*.h
	make -C ${MINISHELL_DIR}
	make -C ${LIBUTILS_DIR}
	gcc ${CFLAGS} ${OBJS} ${MIN_OBJ_DIR}*/*.o ${TEST_UTILS_OBJ_DIR}*.o ${UNITY_OBJ_DIR}*.o -o ${NAME} ${LIBDEBUG} ${LIBFLAGS}

clean:
	${RM} ${OBJ_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re run
