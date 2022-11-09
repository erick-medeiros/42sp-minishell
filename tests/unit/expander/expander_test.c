#include "Unity/unity.h"
#include "expander.h"
#include "minishell.h"
#include "unit_tests_utils.h"
#include <stdlib.h>

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

void test_filename_expander(void) {
	char *result;

	(void)result;
	TEST_ASSERT_EQUAL_STRING(NULL, filename_expander(NULL));
}

int file_expansor_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_expansor_vars);
	RUN_TEST(test_clean_quote_expansor);
	RUN_TEST(test_filename_expander);
	return UNITY_END();
}
