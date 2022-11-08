#include "Unity/unity.h"
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "structs.h"

void test_push_postfix_command(void) {
	t_tree *cmd = new_tree_node(TREE_TYPE_CMD);
	t_node *stack = NULL;
	t_queue cmds;

	cmds.front = NULL;
	cmds.rear = NULL;
	push_postfix(&stack, &cmds, cmd);
	TEST_ASSERT_NOT_EQUAL(NULL, cmds.front);
	TEST_ASSERT_NOT_EQUAL(NULL, cmds.rear);
	TEST_ASSERT_EQUAL(TREE_TYPE_CMD, ((t_tree *)cmds.front->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, stack);
	clear_list(cmds.front, del_cmd_tree_node);
}

void test_push_postfix_pipe(void) {
	t_tree *op = new_tree_node(TREE_TYPE_PIPE);
	t_node *stack = NULL;
	t_queue cmds;

	cmds.front = NULL;
	cmds.rear = NULL;
	push_postfix(&stack, &cmds, op);
	TEST_ASSERT_NOT_EQUAL(NULL, stack);
	TEST_ASSERT_EQUAL(TREE_TYPE_PIPE, ((t_tree *)stack->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, cmds.front);
	TEST_ASSERT_EQUAL_PTR(NULL, cmds.rear);
	clear_list(stack, del_cmd_tree_node);
}

void test_flush_postfix(void) {
	t_tree *op = new_tree_node(TREE_TYPE_PIPE);
	t_node *stack = NULL;
	t_queue cmds;

	cmds.front = NULL;
	cmds.rear = NULL;
	push_postfix(&stack, &cmds, op);
	flush_postfix(&stack, &cmds);
	TEST_ASSERT_NOT_EQUAL(NULL, cmds.front);
	TEST_ASSERT_NOT_EQUAL(NULL, cmds.rear);
	TEST_ASSERT_EQUAL(TREE_TYPE_PIPE, ((t_tree *)cmds.front->content)->type);
	TEST_ASSERT_EQUAL_PTR(NULL, stack);
	clear_list(cmds.front, del_cmd_tree_node);
}

void test_push_postfix_cmd_pipe_cmd_flush(void) {
	t_tree *cmd1 = new_tree_node(TREE_TYPE_CMD);
	t_tree *cmd2 = new_tree_node(TREE_TYPE_CMD);
	t_tree *op = new_tree_node(TREE_TYPE_PIPE);
	t_node *stack = NULL;
	t_queue cmds;

	cmds.front = NULL;
	cmds.rear = NULL;
	cmd1->content = new_command(0);
	cmd2->content = new_command(1);
	push_postfix(&stack, &cmds, cmd1);
	push_postfix(&stack, &cmds, op);
	push_postfix(&stack, &cmds, cmd2);
	flush_postfix(&stack, &cmds);
	TEST_ASSERT_NOT_EQUAL(NULL, cmds.front);
	TEST_ASSERT_NOT_EQUAL(NULL, cmds.rear);
	TEST_ASSERT_EQUAL(TREE_TYPE_CMD, ((t_tree *)cmds.front->content)->type);
	TEST_ASSERT_EQUAL(TREE_TYPE_CMD,
					  ((t_tree *)cmds.front->next->content)->type);
	TEST_ASSERT_EQUAL(TREE_TYPE_PIPE,
					  ((t_tree *)cmds.front->next->next->content)->type);
	TEST_ASSERT_EQUAL_INT(
		0, ((t_cmd *)((t_tree *)cmds.front->content)->content)->number);
	TEST_ASSERT_EQUAL_INT(
		1, ((t_cmd *)((t_tree *)cmds.front->next->content)->content)->number);
	TEST_ASSERT_EQUAL_PTR(NULL,
						  ((t_tree *)cmds.front->next->next->content)->content);
	TEST_ASSERT_EQUAL_PTR(NULL, stack);
	clear_list(cmds.front, del_cmd_tree_node);
}

int file_postfix_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_push_postfix_command);
	RUN_TEST(test_push_postfix_pipe);
	RUN_TEST(test_flush_postfix);
	RUN_TEST(test_push_postfix_cmd_pipe_cmd_flush);
	return UNITY_END();
}
