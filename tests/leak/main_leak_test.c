#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

char *ft_strjoin(char const *s1, char const *s2);
char *get_next_line(int fd);

void child_process(char *test_input, int pipefd[2]) {
	char *extension = strchr(test_input, '.');
	if (extension)
		extension[0] = '\0';
	char logfile[100];
	sprintf(logfile, "logs/%s.log", test_input);
	dup2(pipefd[0], STDIN);
	int fd_devnull = open("/dev/null", O_WRONLY);
	// int fd_log = open(logfile, O_WRONLY);
	dup2(fd_devnull, STDOUT);
	dup2(fd_devnull, STDERR);
	close(fd_devnull);
	close(pipefd[0]);
	close(pipefd[1]);
	char *flaglogfile = ft_strjoin("--log-file=", logfile);
	char *const argv[] = {"./valgrind",		   //
						  "--leak-check=full", //
						  "--show-leak-kinds=all",
						  "--suppressions=../readline.supp", //
						  "--track-fds=yes",				 //
						  "--trace-children=yes",
						  flaglogfile,		 //
						  "../../minishell", //
						  NULL};
	if (execv("/usr/bin/valgrind", argv) == -1)
		exit(1);
}

int run_test(char *test_input) {
	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd) == -1)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
		child_process(test_input, pipefd);
	close(pipefd[0]);
	char path[100];
	sprintf(path, "input/%s", test_input);
	int fd_input = open(path, O_RDONLY);
	char *str;
	str = get_next_line(fd_input);
	while (str) {
		if (str[0] != '#')
			write(pipefd[1], str, strlen(str));
		free(str);
		str = get_next_line(fd_input);
	}
	close(fd_input);
	close(pipefd[1]);
	int status;
	wait(&status);
	return (status);
}

int main(void) {
	struct dirent *direntp;
	DIR *dirp;
	char *directory = "input";

	dirp = opendir(directory);
	if (dirp == NULL) {
		printf("Cannot open directory '%s'\n", directory);
		return 1;
	}
	while ((direntp = readdir(dirp)) != NULL) {
		if (strcmp(".", direntp->d_name) != 0 &&
			strcmp("..", direntp->d_name) != 0) {
			printf("exec [%s]\n", direntp->d_name);
			run_test(direntp->d_name);
		}
	}
	closedir(dirp);
	return 0;
}