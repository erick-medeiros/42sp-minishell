#include "Unity/unity.h"
#include "expander.h"
#include "minishell.h"

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

int file_environment_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_envp_to_list_one_str);
	RUN_TEST(test_envp_to_list_two_str);
	RUN_TEST(test_envp_to_list_no_str);
	RUN_TEST(test_list_to_envp_one_node);
	RUN_TEST(test_list_to_envp_two_nodes);
	RUN_TEST(test_list_to_envp_no_node);
	RUN_TEST(test_list_to_envp_one_node_quoted);
	RUN_TEST(test_list_to_envp_two_nodes_quoted);
	RUN_TEST(test_list_to_envp_no_node_quoted);
	return UNITY_END();
}
