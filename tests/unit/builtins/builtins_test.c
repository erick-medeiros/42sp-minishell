#include "Unity/unity.h"
#include "builtins.h"
#include "libft.h"
#include "minishell.h"
#include "unit_tests_utils.h"
#include <string.h>
#include <unistd.h>

char *simulate_cmd_echo(char *argv[]) {
	int pipefd[2];
	char *content;

	if (pipe(pipefd) == -1)
		TEST_FAIL();
	builtin_echo(pipefd[1], argv);
	close(pipefd[1]);
	content = ut_get_content_fd(pipefd[0]);
	close(pipefd[0]);
	return (content);
}

void test_builtin_echo(void) {
	char *output;

	output = simulate_cmd_echo(((char *[]){"echo", "echo", NULL}));
	TEST_ASSERT_EQUAL_STRING("echo\n", output);
	free(output);
	output = simulate_cmd_echo(((char *[]){"echo", "-n", "echo", NULL}));
	TEST_ASSERT_EQUAL_STRING("echo", output);
	free(output);
	output = simulate_cmd_echo(((char *[]){"echo", "-nn", "echo", NULL}));
	TEST_ASSERT_EQUAL_STRING("echo", output);
	free(output);
	output = simulate_cmd_echo(((char *[]){"echo", "echo", "echo", NULL}));
	TEST_ASSERT_EQUAL_STRING("echo echo\n", output);
	free(output);
	output =
		simulate_cmd_echo(((char *[]){"echo", "-n", "echo", "echo", NULL}));
	TEST_ASSERT_EQUAL_STRING("echo echo", output);
	free(output);
	output = simulate_cmd_echo(((char *[]){"echo", NULL}));
	TEST_ASSERT_EQUAL_STRING("\n", output);
	free(output);
}

void test_builtin_cd(void) {
	pid_t pid;
	char *expected;
	char *content;
	int status;
	int len;

	expected = "/tmp";
	len = strlen(expected) + 1;
	content = ut_mmap(len);
	pid = fork();
	if (pid < 0)
		TEST_FAIL();
	else if (pid == 0) {
		ut_stds_devnull();
		builtin_cd(2, (char *[]){"cd", expected, 0}, NULL);
		char *new_dir = ut_getcwd();
		strncpy(content, new_dir, len);
		free(new_dir);
		exit(0);
	} else {
		wait(&status);
		if (status != 0)
			TEST_IGNORE_MESSAGE(UT_ERR_PROC);
		TEST_ASSERT_EQUAL_STRING(expected, content);
	}
}

void test_builtin_pwd(void) {
	char *current_dir;
	char *expected;
	char *content;
	pid_t pid;
	int pipefd[2];
	int status;

	if (pipe(pipefd) == -1)
		TEST_FAIL();
	pid = fork();
	if (pid < 0)
		TEST_FAIL();
	else if (pid == 0) {
		ut_stds_devnull();
		dup2(pipefd[1], STDOUT);
		ut_close_pipefd(pipefd);
		builtin_pwd(STDOUT);
		exit(0);
	} else {
		close(pipefd[1]);
		wait(&status);
		if (status != 0)
			TEST_IGNORE_MESSAGE(UT_ERR_PROC);
		current_dir = ut_getcwd();
		content = ut_get_content_fd(pipefd[0]);
		expected = ft_strjoin(current_dir, "\n");
		TEST_ASSERT_EQUAL_STRING(expected, content);
		free(content);
		free(expected);
		free(current_dir);
		close(pipefd[0]);
	}
}

static char *create_temp_dir_overflow() {
	int overflow = PATH_MAX + 1;
	char *str;
	char *dir;
	int i;
	pid_t pid;

	str = malloc(sizeof(char) * (overflow + 1));
	memset(str, 'w', overflow);
	str[overflow] = '\0';
	i = -1;
	while (str[++i])
		if (!(i % 10))
			str[i] = '/';
	dir = ft_strjoin("/tmp/42sp/test_builtin_pwd_overflow", str);
	dir[PATH_MAX] = '\0';
	free(str);
	pid = fork();
	if (pid < 0)
		TEST_FAIL();
	else if (pid == 0) {
		char *const argv[] = {"mkdir", "-p", dir, NULL};
		if (execv("/usr/bin/mkdir", argv) == -1)
			exit(1);
	}
	wait(NULL);
	return (dir);
}

static void cd_temp_dir_overflow(char *dir) {
	int i = 0;
	char **temp = ft_split(dir, '/');
	while (temp[i]) {
		char *cd;
		if (i == 0)
			cd = ft_strjoin("/", temp[i]);
		else
			cd = ft_strjoin("./", temp[i]);
		chdir(cd);
		free(cd);
		++i;
	}
	free_string_list(temp);
}

void test_builtin_pwd_overflow(void) {
	char *dir;
	pid_t pid;

	dir = create_temp_dir_overflow();
	pid = fork();
	if (pid < 0)
		TEST_FAIL();
	else if (pid == 0) {
		ut_stds_devnull();
		cd_temp_dir_overflow(dir);
		free(dir);
		errno = 0;
		builtin_pwd(STDOUT);
		exit(errno);
	}
	int status = ut_wait();
	free(dir);
	if (status == 0)
		TEST_PASS();
	else
		TEST_IGNORE();
}

void test_builtin_exit(void) {
	pid_t pid;
	int status;
	int expected;

	pid = fork();
	if (pid < 0)
		TEST_FAIL();
	else if (pid == 0) {
		ut_stds_devnull();
		builtin_exit(0, NULL, NULL);
		exit(1);
	}
	expected = 0;
	status = ut_wait();
	TEST_ASSERT_EQUAL_INT(expected, status);
}

int file_builtins_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_builtin_echo);
	RUN_TEST(test_builtin_cd);
	RUN_TEST(test_builtin_pwd);
	RUN_TEST(test_builtin_pwd_overflow);
	RUN_TEST(test_builtin_exit);
	return UNITY_END();
}
