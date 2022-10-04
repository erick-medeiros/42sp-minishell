#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include "Unity/unity.h"
#include "minishell.h"

// prompt.c
void test_function_command_is_equal(void);
void test_function_command_ends_with(void);
void test_function_get_content_fd(void);

#endif