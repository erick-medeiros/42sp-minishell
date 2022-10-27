#ifndef UNIT_TESTS_UTILS_H
#define UNIT_TESTS_UTILS_H

#include <stddef.h>

#define UT_ERR_ALLOC "Error allocation"

void ut_stds_devnull(void);
void ut_close_pipefd(int pipefd[2]);
char *ut_exec_pwd(void);
void *ut_mmap(size_t len);
char **ut_fake_envp_path(void);

#endif