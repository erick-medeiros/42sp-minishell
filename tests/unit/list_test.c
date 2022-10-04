#include "Unity/unity.h"
#include "minishell.h"

t_node *lst;
int *content1;
int *content2;

void alloc_list(void) {
	lst = NULL;
	content1 = malloc(sizeof(*content1));
	content2 = malloc(sizeof(*content2));
	*content1 = 1;
	*content2 = 2;
}

int cmp_int(void *a, void *b) {
	if (!b && !a)
		return (0);
	if (!b)
		return (1);
	if (!a || *(int *)a < *(int *)b)
		return (-1);
	if (*(int *)a > *(int *)b)
		return (1);
	return (0);
}

void test_create_int_list(void) {
	alloc_list();
	add_node(&lst, content1);
	add_node(&lst, content2);
	TEST_ASSERT_EQUAL_INT(*(int *)lst->content, *content1);
	TEST_ASSERT_EQUAL_INT(*(int *)lst->next->content, *content2);
	TEST_ASSERT_EQUAL_INT(*(int *)lst->content, 1);
	TEST_ASSERT_EQUAL_INT(*(int *)lst->next->content, 2);
	clear_list(lst, del_ptr_content);
}

void test_find_node_by_content_int_list(void) {
	int test_val;
	t_node *cmp_result;

	alloc_list();
	add_node(&lst, content1);
	add_node(&lst, content2);
	test_val = 3;
	cmp_result = find_node_by_content(lst, &test_val, cmp_int);
	TEST_ASSERT_EQUAL_PTR(cmp_result, NULL);
	test_val = 1;
	cmp_result = find_node_by_content(lst, &test_val, cmp_int);
	TEST_ASSERT_EQUAL_PTR(cmp_result, lst);
	test_val = 2;
	cmp_result = find_node_by_content(lst, &test_val, cmp_int);
	TEST_ASSERT_EQUAL_PTR(cmp_result, lst->next);
	cmp_result = find_node_by_content(lst, NULL, cmp_int);
	TEST_ASSERT_EQUAL_PTR(cmp_result, NULL);
	clear_list(lst, del_ptr_content);
}

void test_remove_last_node_int_list(void) {
	int test_val;

	alloc_list();
	add_node(&lst, content1);
	add_node(&lst, content2);
	test_val = remove_node_by_content(&lst, content2, del_ptr_content, cmp_int);
	TEST_ASSERT_EQUAL_INT(test_val, OK);
	TEST_ASSERT_NOT_EQUAL(lst, NULL);
	TEST_ASSERT_EQUAL_PTR(lst->content, content1);
	TEST_ASSERT_EQUAL_PTR(lst->next, NULL);
	clear_list(lst, del_ptr_content);
}

void test_remove_first_node_int_list(void) {
	int test_val;

	alloc_list();
	add_node(&lst, content1);
	add_node(&lst, content2);
	test_val = remove_node_by_content(&lst, content1, del_ptr_content, cmp_int);
	TEST_ASSERT_EQUAL_INT(test_val, OK);
	TEST_ASSERT_NOT_EQUAL(lst, NULL);
	TEST_ASSERT_EQUAL_PTR(lst->content, content2);
	TEST_ASSERT_EQUAL_PTR(lst->next, NULL);
	clear_list(lst, del_ptr_content);
}

void test_remove_mid_node_int_list(void) {
	int test_val;

	alloc_list();
	add_node(&lst, content1);
	add_node(&lst, NULL);
	add_node(&lst, content2);
	test_val = remove_node_by_content(&lst, NULL, del_ptr_content, cmp_int);
	TEST_ASSERT_EQUAL_INT(test_val, OK);
	TEST_ASSERT_NOT_EQUAL(lst, NULL);
	TEST_ASSERT_EQUAL_PTR(lst->content, content1);
	TEST_ASSERT_NOT_EQUAL(lst->next, NULL);
	TEST_ASSERT_EQUAL_PTR(lst->next->content, content2);
	clear_list(lst, del_ptr_content);
}

void test_change_node_content_int_list(void) {
	int test_val;
	int *new_content;

	alloc_list();
	new_content = malloc(sizeof(*new_content));
	add_node(&lst, content1);
	add_node(&lst, content2);
	test_val = change_node_content(lst, content2, new_content, cmp_int);
	TEST_ASSERT_EQUAL_INT(test_val, OK);
	TEST_ASSERT_NOT_EQUAL(lst, NULL);
	TEST_ASSERT_EQUAL_PTR(lst->content, content1);
	TEST_ASSERT_NOT_EQUAL(lst->next, NULL);
	TEST_ASSERT_EQUAL_PTR(lst->next->content, new_content);
	clear_list(lst, del_ptr_content);
}

void file_list_test(void) {
	RUN_TEST(test_create_int_list);
	RUN_TEST(test_find_node_by_content_int_list);
	RUN_TEST(test_remove_last_node_int_list);
	RUN_TEST(test_remove_first_node_int_list);
	RUN_TEST(test_remove_mid_node_int_list);
	RUN_TEST(test_change_node_content_int_list);
}
