#include "Unity/unity.h"
#include <string.h>

int file_list_test(void);
int file_prompt_test(void);
int file_builtins_test(void);
int file_environment_test(void);
int file_parser_test(void);
int file_subshell_test(void);
int file_utils_test(void);
int file_executor_test(void);
int file_lexer_test(void);
int file_pipeline_test(void);
int file_postfix_test(void);
int file_heredoc_test(void);
int file_expander_test(void);
int file_debug_fd(void);
int file_atoll_test(void);

void setUp(void) {}

void tearDown(void) {}

void run_all_test() {
	file_atoll_test();
	file_builtins_test();
	file_environment_test();
	file_executor_test();
	file_heredoc_test();
	file_lexer_test();
	file_list_test();
	file_parser_test();
	file_pipeline_test();
	file_postfix_test();
	file_prompt_test();
	file_subshell_test();
	file_utils_test();
	file_expander_test();
}

int main(int argc, char *argv[]) {
	if (argc == 1)
		run_all_test();
	else {
		char *file = argv[1];
		if (strcmp("atoll", file) == 0)
			return file_atoll_test();
		if (strcmp("builtins", file) == 0)
			return file_builtins_test();
		if (strcmp("environment", file) == 0)
			return file_environment_test();
		if (strcmp("executor", file) == 0)
			file_executor_test();
		if (strcmp("heredoc", file) == 0)
			file_heredoc_test();
		if (strcmp("lexer", file) == 0)
			file_lexer_test();
		if (strcmp("list", file) == 0)
			return file_list_test();
		if (strcmp("parser", file) == 0)
			return file_parser_test();
		if (strcmp("pipeline", file) == 0)
			file_pipeline_test();
		if (strcmp("postfix", file) == 0)
			file_postfix_test();
		if (strcmp("prompt", file) == 0)
			return file_prompt_test();
		if (strcmp("subshell", file) == 0)
			return file_subshell_test();
		if (strcmp("utils", file) == 0)
			return file_utils_test();
		if (!strcmp("expander", file))
			file_expander_test();
	}
	return 0;
}
