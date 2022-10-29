MAKEFLAGS += -s
MINISHELL_DIR = ../
UNIT_DIR = unit/
UNIT_NAME = ${UNIT_DIR}run_unity_tests.out
INTEG_DIR = integration/
INTEG_NAME = ${INTEG_DIR}run_integration_tests.out

RM = rm -fr

runall: all leaks debug_leak_log

all: minishell unit integration

minishell:
	make -C ${MINISHELL_DIR}

unit:
	-make -k -s -C ${UNIT_DIR}

integration:
	-make -k -s -C ${INTEG_DIR}

re: fclean
	make -C ${MINISHELL_DIR} re
	make -C ${UNIT_DIR} re
	make -C ${INTEG_DIR} re
	make all

clean:
	make -C ${MINISHELL_DIR} clean
	make -C ${UNIT_DIR} clean
	make -C ${INTEG_DIR} clean

fclean:
	make -C ${MINISHELL_DIR} fclean
	make -C ${UNIT_DIR} fclean
	make -C ${INTEG_DIR} fclean
	${RM} *.log


leaks:
	echo "\n========================="
	echo "       Unit tests"
	echo "=========================\n"
	-valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--suppressions=readline.supp \
		--track-fds=yes \
		--track-origins=yes \
		--log-file=unity_leak.log \
		./${UNIT_NAME}

	echo "\n==========================="
	echo "    Integration tests"
	echo "===========================\n"
	-valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--suppressions=readline.supp \
		--track-fds=yes \
		--track-origins=yes \
		--log-file=integ_leak.log \
		./${INTEG_NAME}

debug_leak_log:
	echo "\n==========================="
	echo "    Unit test leak log"
	echo "===========================\n"
	echo "FDS:"
	cat unity_leak.log | grep "FILE DESCRIPTORS" | cut -d ' ' -f2- | uniq | sort
	echo "LEAKS:"
	cat unity_leak.log | grep "ERROR SUMMARY" | cut -d ' ' -f2- | uniq | sort

	echo "\n==========================="
	echo " Integration test leak log"
	echo "===========================\n"
	echo "FDS:"
	cat integ_leak.log | grep "FILE DESCRIPTORS" | cut -d ' ' -f2- | uniq | sort
	echo "LEAKS:"
	cat integ_leak.log | grep "ERROR SUMMARY" | cut -d ' ' -f2- | uniq | sort

.PHONY: all debug_leak_log clean fclean integration leaks minishell re runall unit
