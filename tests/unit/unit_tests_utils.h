#ifndef UNIT_TESTS_UTILS_H
#define UNIT_TESTS_UTILS_H

#include <stddef.h>
#include <sys/types.h>

#define UT_ERR_ALLOC "Error allocation"
#define UT_ERR_FORK "Error fork"
#define UT_ERR_PIPE "Error pipe"
#define UT_ERR_PROC "Error child process"

void ut_stds_devnull(void);
void ut_close_pipefd(int pipefd[2]);
char *ut_exec_pwd(void);
void *ut_mmap(size_t len);
char **ut_fake_envp_path(void);
void ut_exit_status(int *status);
void ut_pipe(int *pipefd);
pid_t ut_fork();
int ut_wait();

#endif