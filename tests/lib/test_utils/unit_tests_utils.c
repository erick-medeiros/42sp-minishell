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

int ut_wait() {
	int status;
	wait(&status);
	ut_exit_status(&status);
	return (status);
}

char	*ut_get_content_fd(int fd)
{
	char	buffer[101];
	int		i;
	int		bytes;
	char	*tmp;
	char	*content;

	i = -1;
	while (++i < 101)
		buffer[i] = '\0';
	content = ft_strdup("");
	while (TRUE)
	{
		bytes = read(fd, buffer, 100);
		buffer[bytes] = '\0';
		buffer[bytes] = '\0';
		if (bytes <= 0)
			break ;
		tmp = content;
		content = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	return (content);
}
