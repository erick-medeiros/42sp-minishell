#include "Unity/unity.h"
#include "minishell.h"
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

char *ut_exec_pwd(void) {
	int pipefd[2];
	pid_t pid;
	char *content;
	int status;

	if (pipe(pipefd) == -1)
		TEST_IGNORE_MESSAGE("Error pipe");
	pid = fork();
	if (pid < 0)
		TEST_IGNORE_MESSAGE("Error fork");
	else if (pid == 0) {
		ut_stds_devnull();
		dup2(pipefd[1], STDOUT);
		ut_close_pipefd(pipefd);
		char *const argv[] = {"pwd", NULL};
		if (execv("/usr/bin/pwd", argv) == -1)
			exit(1);
	}
	close(pipefd[1]);
	wait(&status);
	if (status != 0)
		TEST_IGNORE_MESSAGE("Error child process");
	content = get_content_fd(pipefd[0]);
	close(pipefd[0]);
	return (content);
}

void *ut_mmap(size_t len) {
	int prot = PROT_READ | PROT_WRITE;
	int flags = MAP_SHARED | MAP_ANON;
	void *ptr = mmap(NULL, len, prot, flags, 0, 0);
	memset(ptr, 0, len);
	return (ptr);
}
