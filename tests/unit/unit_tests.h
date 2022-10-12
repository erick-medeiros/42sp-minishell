#ifndef UNIT_TESTS_H
# define UNIT_TESTS_H

#define UNITY_CUSTOM_HELP_MSG "minishell"
#define UNITY_FIXTURE_NO_EXTRAS
#define UNITY_OUTPUT_COLOR
#include "Unity/unity.h"
#include "Unity/unity_fixture.h"
#include "minishell.h"

void test_file_list(void);
void test_file_prompt(void);

#endif
