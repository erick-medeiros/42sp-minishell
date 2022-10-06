#include "unit_tests.h"

static void runAllTests(void) {
	RUN_TEST_GROUP(test_prompt);
	RUN_TEST_GROUP(test_list);
}

int main(int argc, const char *argv[]) {
	return UnityMain(argc, argv, runAllTests);
}