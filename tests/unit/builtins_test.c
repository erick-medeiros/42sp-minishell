#include "Unity/unity.h"
#include "minishell.h"
#include <unistd.h>

void test_builtin_echo(void) {
	int pipefd[2];
	pid_t pid;
	char *expected;
	char *content;

	expected = "echo\necho";
	if (pipe(pipefd) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	else if (pid == 0) {
		int fd_devnull = open("/dev/null", O_WRONLY);
		dup2(fd_devnull, STDIN);
		dup2(pipefd[1], STDOUT);
		dup2(fd_devnull, STDERR);
		close(fd_devnull);
		builtin_echo("", "echo");
		builtin_echo("-n", "echo");
		exit(0);
	} else {
		close(pipefd[1]);
		wait(NULL);
		content = get_content_fd(pipefd[0]);
		TEST_ASSERT_EQUAL_STRING(expected, content);
		free(content);
		close(pipefd[0]);
	}
}

void file_builtins_test(void) { RUN_TEST(test_builtin_echo); }
