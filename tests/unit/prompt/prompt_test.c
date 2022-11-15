#include "Unity/unity.h"
#include "minishell.h"
#include "unit_tests_utils.h"
#include <string.h>
#include <unistd.h>

void test_here_doc(void) {
	int pipefd[2];
	char *expected;
	char *write_line1;
	char *write_line2;
	char *string;
	int len;
	pid_t pid;

	write_line1 = "42\n";
	write_line2 = "sp\n";
	expected = "42\nsp\n";
	len = strlen(write_line1) + strlen(write_line2) + 1;
	string = ut_mmap(sizeof(char) * len);
	if (pipe(pipefd) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	else if (pid == 0) {
		ut_stds_devnull();
		dup2(pipefd[0], STDIN);
		ut_close_pipefd(pipefd);
		int fd = here_doc("EOF");
		char *content = ut_get_content_fd(fd);
		strncpy(string, content, len);
		free(content);
		close(fd);
		exit(0);
	} else {
		write(pipefd[1], write_line1, strlen(write_line1));
		write(pipefd[1], write_line2, strlen(write_line2));
		write(pipefd[1], "EOF", 3);
		ut_close_pipefd(pipefd);
		wait(NULL);
		TEST_ASSERT_EQUAL_STRING(expected, string);
	}
}

int file_prompt_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_here_doc);
	return UNITY_END();
}
