MINISHELL_DIR = ../../
MIN_INC_DIR = $(MINISHELL_DIR)include/
LIBFT_DIR = $(MINISHELL_DIR)libft/

UNITY_SRC_DIR = ./Unity/
UNITY_OBJ_DIR = ../obj/Unity/
UNITY_SRC_FILES = ${wildcard ${UNITY_SRC_DIR}*.c}
UNITY_OBJ_FILES = ${addprefix ${UNITY_OBJ_DIR}, ${notdir ${UNITY_SRC_FILES:.c=.o}}}

TEST_UTILS_SRC_DIR = ./test_utils/
TEST_UTILS_OBJ_DIR = ../obj/test_utils/
TEST_UTILS_SRC_FILES = ${wildcard ${TEST_UTILS_SRC_DIR}*.c}
TEST_UTILS_OBJ_FILES = ${addprefix ${TEST_UTILS_OBJ_DIR}, ${notdir ${TEST_UTILS_SRC_FILES:.c=.o}}}

CC = cc
CFLAGS = -Wall -Wextra -Werror
UNITY_CFLAGS += -O3 -I.
TEST_UTILS_CFLAGS += -O3 -I. -I${TEST_UTILS_SRC_DIR} -I${MIN_INC_DIR} -I${LIBFT_DIR}
RM = rm -fr
REQUIRED_DIRS = ${UNITY_OBJ_DIR} ${TEST_UTILS_OBJ_DIR}

all: test_utils unity

unity: ${UNITY_OBJ_FILES}

test_utils: ${TEST_UTILS_OBJ_FILES}

${TEST_UTILS_OBJ_DIR}%.o: ${TEST_UTILS_SRC_DIR}%.c ${TEST_UTILS_OBJ_DIR} ${TEST_UTILS_SRC_DIR}*.h ${LIBFT_DIR}*.h ${MIN_INC_DIR}*.h
	${CC} ${CFLAGS} ${TEST_UTILS_CFLAGS} -c $< -o $@

${UNITY_OBJ_DIR}%.o: ${UNITY_SRC_DIR}%.c ${UNITY_SRC_DIR}*.h ${UNITY_OBJ_DIR}
	${CC} ${CFLAGS} ${UNITY_CFLAGS} -c $< -o $@

${REQUIRED_DIRS}:
	mkdir -p $@

clean:
	${RM} ${UNITY_OBJ_DIR}
	${RM} ${TEST_UTILS_OBJ_DIR}

fclean: clean

re: fclean all

.PHONY: all clean fclean re test_utils unity
