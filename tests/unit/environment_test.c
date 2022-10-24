#include "Unity/unity.h"
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

void test_envp_to_list_one_str(void) {
	char *str1 = "str1_name=str1_val";
	char *envp[] = {str1, NULL};
	t_vlst vars;

	envp_to_list(envp, &vars);
	TEST_ASSERT_NOT_EQUAL(NULL, vars.list);
	TEST_ASSERT_EQUAL_size_t(1, vars.len);
	TEST_ASSERT_NOT_EQUAL(NULL, vars.list->content);
	TEST_ASSERT_EQUAL_PTR(NULL, vars.list->next);
	TEST_ASSERT_EQUAL_STRING("str1_name", ((t_var *)vars.list->content)->name);
	TEST_ASSERT_EQUAL_STRING("str1_val", ((t_var *)vars.list->content)->val);
	clear_list(vars.list, del_var_node);
}

void test_envp_to_list_two_str(void) {
	char *str1 = "str1_name=str1_val";
	char *str2 = "str2_name=str2_val";
	char *envp[] = {str1, str2, NULL};
	t_vlst vars;
	t_var *var;

	envp_to_list(envp, &vars);
	TEST_ASSERT_NOT_EQUAL(NULL, vars.list);
	TEST_ASSERT_EQUAL_size_t(2, vars.len);
	TEST_ASSERT_NOT_EQUAL(NULL, vars.list->content);
	var = ((t_var *)vars.list->content);
	TEST_ASSERT_EQUAL_STRING("str1_name", var->name);
	TEST_ASSERT_EQUAL_STRING("str1_val", var->val);
	TEST_ASSERT_NOT_EQUAL(NULL, vars.list->next);
	TEST_ASSERT_NOT_EQUAL(NULL, vars.list->next->content);
	var = ((t_var *)vars.list->next->content);
	TEST_ASSERT_EQUAL_STRING("str2_name", var->name);
	TEST_ASSERT_EQUAL_STRING("str2_val", var->val);
	TEST_ASSERT_EQUAL_PTR(NULL, vars.list->next->next);
	clear_list(vars.list, del_var_node);
}

void test_envp_to_list_no_str(void) {
	char *envp[] = {NULL};
	t_vlst vars;

	envp_to_list(envp, &vars);
	TEST_ASSERT_EQUAL_PTR(NULL, vars.list);
	TEST_ASSERT_EQUAL_size_t(0, vars.len);
}

void test_list_to_envp_one_node(void) {
	char **envp;
	t_vlst vars;

	vars.list = NULL;
	add_node(&(vars.list), new_var_node_from_str("name1=val1"));
	vars.len = 1;
	TEST_ASSERT_EQUAL_STRING("name1", ((t_var *)vars.list->content)->name);
	TEST_ASSERT_EQUAL_STRING("val1", ((t_var *)vars.list->content)->val);
	TEST_ASSERT_EQUAL_PTR(NULL, vars.list->next);
	envp = list_to_envp(&vars, 0);
	TEST_ASSERT_NOT_EQUAL(NULL, envp);
	TEST_ASSERT_NOT_EQUAL(NULL, envp[0]);
	TEST_ASSERT_EQUAL_STRING("name1=val1", envp[0]);
	TEST_ASSERT_EQUAL_PTR(NULL, envp[1]);
	clear_list(vars.list, del_var_node);
	clear_envp(envp);
}

void test_list_to_envp_two_nodes(void) {
	char **envp;
	t_vlst vars;
	t_var *var;

	vars.list = NULL;
	add_node(&(vars.list), new_var_node_from_str("name1=val1"));
	add_node(&(vars.list), new_var_node_from_str("name2=val2"));
	vars.len = 2;
	var = ((t_var *)vars.list->content);
	TEST_ASSERT_EQUAL_STRING("name1", var->name);
	TEST_ASSERT_EQUAL_STRING("val1", var->val);
	TEST_ASSERT_NOT_EQUAL(NULL, vars.list->next);
	var = ((t_var *)vars.list->next->content);
	TEST_ASSERT_EQUAL_STRING("name2", var->name);
	TEST_ASSERT_EQUAL_STRING("val2", var->val);
	TEST_ASSERT_EQUAL_PTR(NULL, vars.list->next->next);
	envp = list_to_envp(&vars, 0);
	TEST_ASSERT_NOT_EQUAL(NULL, envp);
	TEST_ASSERT_NOT_EQUAL(NULL, envp[0]);
	TEST_ASSERT_NOT_EQUAL(NULL, envp[1]);
	TEST_ASSERT_EQUAL_STRING("name1=val1", envp[0]);
	TEST_ASSERT_EQUAL_STRING("name2=val2", envp[1]);
	TEST_ASSERT_EQUAL_PTR(NULL, envp[2]);
	clear_list(vars.list, del_var_node);
	clear_envp(envp);
}

void test_list_to_envp_no_node(void) {
	char **envp;
	t_vlst vars;

	vars.list = NULL;
	vars.len = 0;
	TEST_ASSERT_EQUAL_PTR(NULL, vars.list);
	envp = list_to_envp(&vars, 0);
	TEST_ASSERT_NOT_EQUAL(NULL, envp);
	TEST_ASSERT_EQUAL_PTR(NULL, envp[0]);
	clear_envp(envp);
}

void test_list_to_envp_one_node_quoted(void) {
	char **envp;
	t_vlst vars;

	vars.list = NULL;
	add_node(&(vars.list), new_var_node_from_str("name1=val1"));
	vars.len = 1;
	TEST_ASSERT_EQUAL_STRING("name1", ((t_var *)vars.list->content)->name);
	TEST_ASSERT_EQUAL_STRING("val1", ((t_var *)vars.list->content)->val);
	TEST_ASSERT_EQUAL_PTR(NULL, vars.list->next);
	envp = list_to_envp(&vars, 1);
	TEST_ASSERT_NOT_EQUAL(NULL, envp);
	TEST_ASSERT_NOT_EQUAL(NULL, envp[0]);
	TEST_ASSERT_EQUAL_STRING("name1=\"val1\"", envp[0]);
	TEST_ASSERT_EQUAL_PTR(NULL, envp[1]);
	clear_list(vars.list, del_var_node);
	clear_envp(envp);
}

void test_list_to_envp_two_nodes_quoted(void) {
	char **envp;
	t_vlst vars;
	t_var *var;

	vars.list = NULL;
	add_node(&(vars.list), new_var_node_from_str("name1=val1"));
	add_node(&(vars.list), new_var_node_from_str("name2=val2"));
	vars.len = 2;
	var = ((t_var *)vars.list->content);
	TEST_ASSERT_EQUAL_STRING("name1", var->name);
	TEST_ASSERT_EQUAL_STRING("val1", var->val);
	TEST_ASSERT_NOT_EQUAL(NULL, vars.list->next);
	var = ((t_var *)vars.list->next->content);
	TEST_ASSERT_EQUAL_STRING("name2", var->name);
	TEST_ASSERT_EQUAL_STRING("val2", var->val);
	TEST_ASSERT_EQUAL_PTR(NULL, vars.list->next->next);
	envp = list_to_envp(&vars, 1);
	TEST_ASSERT_NOT_EQUAL(NULL, envp);
	TEST_ASSERT_NOT_EQUAL(NULL, envp[0]);
	TEST_ASSERT_NOT_EQUAL(NULL, envp[1]);
	TEST_ASSERT_EQUAL_STRING("name1=\"val1\"", envp[0]);
	TEST_ASSERT_EQUAL_STRING("name2=\"val2\"", envp[1]);
	TEST_ASSERT_EQUAL_PTR(NULL, envp[2]);
	clear_list(vars.list, del_var_node);
	clear_envp(envp);
}

void test_list_to_envp_no_node_quoted(void) {
	char **envp;
	t_vlst vars;

	vars.list = NULL;
	vars.len = 0;
	TEST_ASSERT_EQUAL_PTR(NULL, vars.list);
	envp = list_to_envp(&vars, 1);
	TEST_ASSERT_NOT_EQUAL(NULL, envp);
	TEST_ASSERT_EQUAL_PTR(NULL, envp[0]);
	clear_envp(envp);
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
	RUN_TEST(test_envp_to_list_one_str);
	RUN_TEST(test_envp_to_list_two_str);
	RUN_TEST(test_envp_to_list_no_str);
	RUN_TEST(test_list_to_envp_one_node);
	RUN_TEST(test_list_to_envp_two_nodes);
	RUN_TEST(test_list_to_envp_no_node);
	RUN_TEST(test_list_to_envp_one_node_quoted);
	RUN_TEST(test_list_to_envp_two_nodes_quoted);
	RUN_TEST(test_list_to_envp_no_node_quoted);
	RUN_TEST(test_cmp_vars_by_name_a_is_null);
	RUN_TEST(test_cmp_vars_by_name_b_is_null);
	RUN_TEST(test_cmp_vars_by_name_both_are_null);
	RUN_TEST(test_cmp_vars_by_name_a_is_longer);
	RUN_TEST(test_cmp_vars_by_name_b_is_longer);
	RUN_TEST(test_cmp_vars_by_name_same_names);
	return UNITY_END();
}
