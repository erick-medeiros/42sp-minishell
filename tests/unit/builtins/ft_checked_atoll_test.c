#include "Unity/unity.h"
#include "libft.h"
#include <limits.h>

void test_zero(void) {
	long long int result;
	long long int expected = 0;
	int invalid = 0;
	char *str = "0";

	result = ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT64(expected, result);
	TEST_ASSERT_EQUAL_INT(0, invalid);
}

void test_zero_spaces(void) {
	long long int result;
	long long int expected = 0;
	int invalid = 0;
	char *str = "0";

	result = ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT64(expected, result);
	TEST_ASSERT_EQUAL_INT(0, invalid);
}

void test_zero_plus(void) {
	long long int result;
	long long int expected = 0;
	int invalid = 0;
	char *str = "+0";

	result = ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT64(expected, result);
	TEST_ASSERT_EQUAL_INT(0, invalid);
}

void test_zero_minus(void) {
	long long int result;
	long long int expected = 0;
	int invalid = 0;
	char *str = "-0";

	result = ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT64(expected, result);
	TEST_ASSERT_EQUAL_INT(0, invalid);
}

void test_zero_space_plus(void) {
	long long int result;
	long long int expected = 0;
	int invalid = 0;
	char *str = " +0";

	result = ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT64(expected, result);
	TEST_ASSERT_EQUAL_INT(0, invalid);
}

void test_zero_space_minus(void) {
	long long int result;
	long long int expected = 0;
	int invalid = 0;
	char *str = " -0";

	result = ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT64(expected, result);
	TEST_ASSERT_EQUAL_INT(0, invalid);
}

void test_max(void) {
	long long int result;
	long long int expected = LLONG_MAX;
	int invalid = 0;
	char *str = "9223372036854775807";

	result = ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT64(expected, result);
	TEST_ASSERT_EQUAL_INT(0, invalid);
}

void test_min(void) {
	long long int result;
	long long int expected = LLONG_MIN;
	int invalid = 0;
	char *str = "-9223372036854775808";

	result = ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT64(expected, result);
	TEST_ASSERT_EQUAL_INT(0, invalid);
}

void test_max_plus_one(void) {
	int invalid = 0;
	char *str = "9223372036854775808";
	ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT(1, invalid);
}

void test_min_minus_one(void) {
	int invalid = 0;
	char *str = "-9223372036854775809";

	ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT(1, invalid);
}

void test_not_a_number(void) {
	int invalid = 0;
	char *str = "blah";

	ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT(1, invalid);
}

void test_mixed_number(void) {
	int invalid = 0;
	char *str = "42blah";

	ft_checked_atoll(str, &invalid);
	TEST_ASSERT_EQUAL_INT(1, invalid);
}

int file_atoll_test(void) {
	UNITY_BEGIN();
	RUN_TEST(test_zero);
	RUN_TEST(test_zero_spaces);
	RUN_TEST(test_zero_plus);
	RUN_TEST(test_zero_minus);
	RUN_TEST(test_zero_space_plus);
	RUN_TEST(test_zero_space_minus);
	RUN_TEST(test_max);
	RUN_TEST(test_min);
	RUN_TEST(test_max_plus_one);
	RUN_TEST(test_min_minus_one);
	RUN_TEST(test_not_a_number);
	RUN_TEST(test_mixed_number);
	return UNITY_END();
}
