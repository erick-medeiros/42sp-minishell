NAME = run.out
MINISHELL = ../../minishell

all: $(NAME)

%.o: %.c
	cc -c $< -o $@

$(NAME): $(MINISHELL) get_next_line.o main_leak_test.o
	cc *.o -o $(NAME)

clean:
	rm -fr *.o

fclean: clean
	rm -fr $(NAME)

leaks:
	valgrind ./$(NAME)

report: $(NAME)
	@rm -fr logs/*.log
	./$(NAME)
	@echo "FDS>"
	@cat logs/*.log | grep "FILE DESCRIPTORS" | cut -d ' ' -f2- | uniq | sort
	@echo "LEAKS>"
	@cat logs/*.log | grep "ERROR SUMMARY" | cut -d ' ' -f2- | uniq | sort