#include "Unity/unity.h"
#include "expander.h"
#include "minishell.h"
#include "unit_tests_utils.h"
#include <stdlib.h>
#include <unistd.h>

void test_expansor_vars(void) {
	t_vlst env_list;
	char *envp[] = {"a=bc", "c=de", "$=42", NULL};
	char *str;

	envp_to_list(envp, &env_list);
	str = expansor_vars(&env_list, strdup("$a"));
	TEST_ASSERT_EQUAL_STRING("bc", str);
	free(str);
	str = expansor_vars(&env_list, strdup("${a}d"));
	TEST_ASSERT_EQUAL_STRING("bcd", str);
	free(str);
	str = expansor_vars(&env_list, strdup("$a d"));
	TEST_ASSERT_EQUAL_STRING("bc d", str);
	free(str);
	str = expansor_vars(&env_list, strdup("d $a e"));
	TEST_ASSERT_EQUAL_STRING("d bc e", str);
	free(str);
	str = expansor_vars(&env_list, strdup("a$a${c}f"));
	TEST_ASSERT_EQUAL_STRING("abcdef", str);
	free(str);
	str = expansor_vars(&env_list, strdup("$$$"));
	TEST_ASSERT_EQUAL_STRING("42$", str);
	free(str);
	clear_list(env_list.list, del_var_node);
	// str = expansor_vars(&env_list, strdup("$?"));
	// str = expansor_vars(&env_list, strdup("$_"));
}

void test_clean_quote_expansor(void) {
	char *str;

	str = clean_quote_expansor(strdup("\"abc'def\""));
	TEST_ASSERT_EQUAL_STRING("abc'def", str);
	free(str);
	str = clean_quote_expansor(strdup("\"abc'def\"'abc\"def'"));
	TEST_ASSERT_EQUAL_STRING("abc'defabc\"def", str);
	free(str);
	str = clean_quote_expansor(strdup("abc"));
	TEST_ASSERT_EQUAL_STRING("abc", str);
	free(str);
}

char *simulate_bash_exec(char *exec) {
	int pipefd[2];
	char *result;

	if (pipe(pipefd) == -1)
		TEST_FAIL();
	pid_t pid = fork();
	if (pid < 0)
		TEST_FAIL();
	else if (pid == 0) {
		ut_stds_devnull();
		dup2(pipefd[1], STDOUT);
		ut_close_pipefd(pipefd);
		char *argv[] = {"bash", "-c", exec, NULL};
		execv("/usr/bin/bash", argv);
		exit(1);
	}
	int status;
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	ut_exit_status(&status);
	result = get_content_fd(pipefd[0]);
	close(pipefd[0]);
	return (result);
}

void test_filename_expander(void) {
	char *expected;
	char *result;

	TEST_ASSERT_EQUAL_STRING(NULL, filename_expander(NULL));
	expected = simulate_bash_exec("echo -n *");
	result = filename_expander("*");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	expected = simulate_bash_exec("echo -n *.c");
	result = filename_expander("*.c");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	expected = simulate_bash_exec("echo -n M*");
	result = filename_expander("M*");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	expected = simulate_bash_exec("echo -n *k*");
	result = filename_expander("*k*");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	result = filename_expander("abc");
	TEST_ASSERT_EQUAL_STRING("abc", result);
	free(result);
	expected = simulate_bash_exec("echo -n .*");
	result = filename_expander(".*");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	expected = simulate_bash_exec("echo -n *e");
	result = filename_expander("*e");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
}

int file_expander_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_expansor_vars);
	RUN_TEST(test_clean_quote_expansor);
	RUN_TEST(test_filename_expander);
	return UNITY_END();
}
