#include "unit_tests_utils.h"
#include "Unity/unity.h"
#include "minishell.h"
#include <limits.h>
#include <linux/limits.h>
#include <stddef.h>
#include <sys/mman.h>

void ut_stds_devnull(void) {
	int fd_devnull = open("/dev/null", O_WRONLY);
	dup2(fd_devnull, STDIN);
	dup2(fd_devnull, STDOUT);
	dup2(fd_devnull, STDERR);
	close(fd_devnull);
}

void ut_close_pipefd(int pipefd[2]) {
	close(pipefd[0]);
	close(pipefd[1]);
}

char *ut_getcwd() {
	char *cwd = getcwd(NULL, PATH_MAX);
	if (!cwd)
		TEST_IGNORE_MESSAGE("Error: get current working directory failed\n");
	return (cwd);
}

void *ut_mmap(size_t len) {
	int prot = PROT_READ | PROT_WRITE;
	int flags = MAP_SHARED | MAP_ANON;
	void *ptr = mmap(NULL, len, prot, flags, 0, 0);
	memset(ptr, 0, len);
	return (ptr);
}

char **ut_fake_envp_path(void) {
	char *env_path;
	char **fake_envp;

	env_path = getenv("PATH");
	if (!env_path)
		TEST_IGNORE_MESSAGE("Error getenv returned NULL");
	fake_envp = malloc(sizeof(char *) * 2);
	if (!fake_envp)
		TEST_IGNORE_MESSAGE(UT_ERR_ALLOC);
	fake_envp[0] = ft_strjoin("PATH=", env_path);
	fake_envp[1] = NULL;
	return (fake_envp);
}

void ut_exit_status(int *status) {
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
}

void ut_pipe(int *pipefd) {
	if (pipe(pipefd) == -1)
		TEST_IGNORE_MESSAGE(UT_ERR_PIPE);
}

pid_t ut_fork() {
	pid_t pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE(UT_ERR_FORK);
	return (pid);
}

int ut_wait() {
	int status;
	wait(&status);
	ut_exit_status(&status);
	return (status);
}
