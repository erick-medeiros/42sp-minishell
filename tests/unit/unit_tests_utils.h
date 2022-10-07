#ifndef UNIT_TESTS_UTILS_H
#define UNIT_TESTS_UTILS_H

#include <stddef.h>

void ut_stds_devnull(void);
void ut_close_pipefd(int pipefd[2]);
char *ut_exec_pwd(void);
void *ut_mmap(size_t len);

#endif