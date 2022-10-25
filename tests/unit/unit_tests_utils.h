#ifndef UNIT_TESTS_UTILS_H
#define UNIT_TESTS_UTILS_H

#include <stddef.h>

#define UT_ERR_ALLOC "Error allocation"
#define UT_ERR_FORK "Error fork"

void ut_stds_devnull(void);
void ut_close_pipefd(int pipefd[2]);
char *ut_exec_pwd(void);
void *ut_mmap(size_t len);
char **ut_fake_envp_path(void);
void ut_exit_status(int *status);

#endif