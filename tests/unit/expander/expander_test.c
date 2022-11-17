#include "Unity/unity.h"
#include "expander.h"
#include "minishell.h"
#include "structs.h"
#include "unit_tests_utils.h"
#include <stdlib.h>
#include <unistd.h>

void test_expansor_vars(void) {
	t_minishell ms;
	char *envp[] = {"a=bc", "c=de", NULL};
	char *str;
	init_minishell(&ms, envp);

	str = parameter_expansion("$a", &ms.env_list, 0);
	TEST_ASSERT_EQUAL_STRING("bc", str);
	free(str);
	str = parameter_expansion("${a}d", &ms.env_list, 0);
	TEST_ASSERT_EQUAL_STRING("bcd", str);
	free(str);
	str = parameter_expansion("$a d", &ms.env_list, 0);
	TEST_ASSERT_EQUAL_STRING("bc d", str);
	free(str);
	str = parameter_expansion("d $a e", &ms.env_list, 0);
	TEST_ASSERT_EQUAL_STRING("d bc e", str);
	free(str);
	str = parameter_expansion("a$a${c}f", &ms.env_list, 0);
	TEST_ASSERT_EQUAL_STRING("abcdef", str);
	free(str);
	destroy_minishell(&ms);
}

void test_remove_quote(void) {
	char *str;

	str = remove_quote("\"abc'def\"");
	TEST_ASSERT_EQUAL_STRING("abc'def", str);
	free(str);
	str = remove_quote("\"abc'def\"'abc\"def'");
	TEST_ASSERT_EQUAL_STRING("abc'defabc\"def", str);
	free(str);
	str = remove_quote("abc");
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
		char *envp[] = {"LC_ALL=C", NULL};
		execve("/usr/bin/bash", argv, envp);
		exit(1);
	}
	int status;
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	ut_exit_status(&status);
	result = ut_get_content_fd(pipefd[0]);
	close(pipefd[0]);
	return (result);
}

void test_expand_filename(void) {
	char *expected;
	char *result;

	TEST_ASSERT_EQUAL_STRING(NULL, expand_filename(NULL));
	expected = simulate_bash_exec("echo -n *");
	result = expand_filename("*");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	expected = simulate_bash_exec("echo -n *.c");
	result = expand_filename("*.c");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	expected = simulate_bash_exec("echo -n M*");
	result = expand_filename("M*");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	expected = simulate_bash_exec("echo -n *k*");
	result = expand_filename("*k*");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	result = expand_filename("abc");
	TEST_ASSERT_EQUAL_STRING("abc", result);
	free(result);
	expected = simulate_bash_exec("echo -n .*");
	result = expand_filename(".*");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	expected = simulate_bash_exec("echo -n *e");
	result = expand_filename("*e");
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(expected);
	free(result);
	// integ_leak.log integration in.txt
}

void test_convert_list_to_string() {
	t_node *list;
	const char *expected = "abcdef";
	char *result;

	list = NULL;
	//
	result = convert_list_to_string(list);
	TEST_ASSERT_EQUAL_STRING("", result);
	free(result);
	//
	add_node(&list, strdup("abc"));
	add_node(&list, strdup("de"));
	add_node(&list, strdup("f"));
	result = convert_list_to_string(list);
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(result);
}

void test_parameter_expansion() {
	t_vlst vars;
	envp_to_list((char *[]){"SHELL=minishell", NULL}, &vars);
	char *result = parameter_expansion("echo $SHELL $? ${SHELL}abc", &vars, 0);
	TEST_ASSERT_EQUAL_STRING("echo minishell 0 minishellabc", result);
	free(result);
	clear_list(vars.list, del_var_node);
}

int file_expander_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_expansor_vars);
	RUN_TEST(test_remove_quote);
	RUN_TEST(test_expand_filename);
	RUN_TEST(test_convert_list_to_string);
	RUN_TEST(test_parameter_expansion);
	return UNITY_END();
}
