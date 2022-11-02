#include "Unity/unity.h"
#include "expansor.h"
#include "minishell.h"
#include "unit_tests_utils.h"
#include <stdlib.h>

void test_function_get_paths(void) {
	char *env_path;
	char **fake_envp;
	char **paths;
	char **paths_compare;
	char *compare;
	int i;

	env_path = getenv("PATH");
	if (!env_path)
		TEST_IGNORE_MESSAGE("Error getenv returned NULL");
	fake_envp = ut_fake_envp_path();
	paths_compare = ft_split(env_path, ':');
	paths = get_paths(fake_envp);
	TEST_ASSERT(paths);
	TEST_ASSERT_NOT_EQUAL(NULL, *paths);
	i = 0;
	while (paths_compare[i] && paths[i]) {
		compare = ft_strjoin(paths_compare[i], "/");
		TEST_ASSERT_EQUAL_STRING(compare, paths[i]);
		free(compare);
		free(paths_compare[i]);
		free(paths[i]);
		++i;
	}
	TEST_ASSERT_EQUAL_STRING(paths_compare[i], paths[i]);
	free(paths_compare);
	free(paths);
	free(fake_envp[0]);
	free(fake_envp);
}

void test_function_get_pathname(void) {
	char **fake_envp;
	char *pathname;

	fake_envp = ut_fake_envp_path();
	pathname = get_pathname("echo", fake_envp);
	TEST_ASSERT_EQUAL_STRING("/usr/bin/echo", pathname);
	free(pathname);
	free_string_list(fake_envp);
}

int file_pathname_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_function_get_paths);
	RUN_TEST(test_function_get_pathname);
	return UNITY_END();
}