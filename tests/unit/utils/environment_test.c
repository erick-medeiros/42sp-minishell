#include "Unity/unity.h"
#include "expander.h"
#include "minishell.h"

void test_new_var_node_contains_equal(void) {
	char *str;
	t_var *content;

	str = ft_strdup("nome_teste=val_teste");
	content = new_var_node_from_str(str);
	TEST_ASSERT_NOT_EQUAL(NULL, str);
	TEST_ASSERT_NOT_EQUAL(NULL, content);
	TEST_ASSERT_NOT_EQUAL(NULL, content->name);
	TEST_ASSERT_NOT_EQUAL(NULL, content->val);
	TEST_ASSERT_EQUAL_STRING("nome_teste", content->name);
	TEST_ASSERT_EQUAL_STRING("val_teste", content->val);
	del_var_node(content);
	free(str);
}

void test_new_var_node_contains_no_equal(void) {
	char *str;
	t_var *content;

	str = ft_strdup("nome_testeval_teste");
	content = new_var_node_from_str(str);
	TEST_ASSERT_NOT_EQUAL(NULL, str);
	TEST_ASSERT_EQUAL(NULL, content);
	free(str);
}

void test_new_var_node_null_str(void) {
	char *str;
	t_var *content;

	str = NULL;
	content = new_var_node_from_str(str);
	TEST_ASSERT_EQUAL(NULL, str);
	TEST_ASSERT_EQUAL(NULL, content);
}

void test_cmp_vars_by_name_a_is_null(void) {
	t_var a;
	t_var b;
	int result;

	a = (t_var){.name = NULL, .val = "val1"};
	b = (t_var){.name = "name2", .val = "val2"};

	result = cmp_vars_by_name(&a, &b);
	TEST_ASSERT_LESS_OR_EQUAL_INT(-1, result);
	result = cmp_vars_by_name(NULL, &b);
	TEST_ASSERT_LESS_OR_EQUAL_INT(-1, result);
}

void test_cmp_vars_by_name_b_is_null(void) {
	t_var a;
	t_var b;
	int result;

	a = (t_var){.name = "name1", .val = "val1"};
	b = (t_var){.name = NULL, .val = "val2"};

	result = cmp_vars_by_name(&a, &b);
	TEST_ASSERT_GREATER_OR_EQUAL_INT(1, result);
	result = cmp_vars_by_name(&a, NULL);
	TEST_ASSERT_GREATER_OR_EQUAL_INT(1, result);
}

void test_cmp_vars_by_name_both_are_null(void) {
	t_var a;
	t_var b;
	int result;

	a = (t_var){.name = NULL, .val = "val1"};
	b = (t_var){.name = NULL, .val = "val2"};

	result = cmp_vars_by_name(&a, &b);
	TEST_ASSERT_EQUAL_INT(0, result);
	result = cmp_vars_by_name(NULL, NULL);
	TEST_ASSERT_EQUAL_INT(0, result);
}

void test_cmp_vars_by_name_a_is_longer(void) {
	t_var a;
	t_var b;
	int result;

	a = (t_var){.name = "name is long", .val = "val1"};
	b = (t_var){.name = "name", .val = "val2"};

	result = cmp_vars_by_name(&a, &b);
	TEST_ASSERT_GREATER_OR_EQUAL_INT(1, result);
}

void test_cmp_vars_by_name_b_is_longer(void) {
	t_var a;
	t_var b;
	int result;

	a = (t_var){.name = "name", .val = "val1"};
	b = (t_var){.name = "name is long", .val = "val2"};

	result = cmp_vars_by_name(&a, &b);
	TEST_ASSERT_LESS_OR_EQUAL_INT(-1, result);
}

void test_cmp_vars_by_name_same_names(void) {
	t_var a;
	t_var b;
	int result;

	a = (t_var){.name = "name", .val = "val1"};
	b = (t_var){.name = "name", .val = "val2"};

	result = cmp_vars_by_name(&a, &b);
	TEST_ASSERT_EQUAL_INT(0, result);
}

int file_environment_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_new_var_node_contains_equal);
	RUN_TEST(test_new_var_node_contains_no_equal);
	RUN_TEST(test_new_var_node_null_str);
	RUN_TEST(test_cmp_vars_by_name_a_is_null);
	RUN_TEST(test_cmp_vars_by_name_b_is_null);
	RUN_TEST(test_cmp_vars_by_name_both_are_null);
	RUN_TEST(test_cmp_vars_by_name_a_is_longer);
	RUN_TEST(test_cmp_vars_by_name_b_is_longer);
	RUN_TEST(test_cmp_vars_by_name_same_names);
	return UNITY_END();
}
