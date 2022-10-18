NAME = run.out
MINISHELL = ../../minishell
REQUIRED_DIRS = logs
OBJ = get_next_line.o main_leak_test.o

all: $(NAME)

$(REQUIRED_DIRS):
	@mkdir -p $@

%.o: %.c
	cc -c $< -o $@

$(NAME): $(REQUIRED_DIRS) $(MINISHELL) $(OBJ)
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