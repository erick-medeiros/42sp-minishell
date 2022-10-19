#include <bsd/string.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1000
#define FD_LIMIT 1024

char *ft_strjoin(char const *s1, char const *s2) {
	char *result = malloc(strlen(s1) + strlen(s2) + 1);
	if (result) {
		strcpy(result, s1);
		strcat(result, s2);
	}
	return result;
}

char *ft_substr(char const *s, unsigned int start, size_t len) {
	char *sub;

	if (!s)
		return (NULL);
	if (start > strlen(s))
		return (strdup(""));
	sub = strdup(s);
	strlcpy(sub, &s[start], len);
	return (sub);
}

static char *get_line(char **acc) {
	size_t c;
	char *s;
	char *r;

	if (*acc == NULL)
		return (NULL);
	c = (size_t)(strchr(*acc, '\n') - *acc) + 1;
	s = ft_substr(*acc, 0, c);
	r = ft_substr(*acc, c, strlen(*acc));
	free(*acc);
	*acc = NULL;
	if (r && r[0] == '\0')
		free(r);
	else
		*acc = r;
	return (s);
}

static void read_line(int fd, char **acc, char *buffer) {
	int read_bytes;
	char *tmp;

	while (1) {
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1 || read_bytes == 0)
			break;
		buffer[read_bytes] = '\0';
		if (*acc == NULL)
			*acc = strdup("");
		tmp = *acc;
		*acc = ft_strjoin(*acc, buffer);
		free(tmp);
		if (strchr(buffer, '\n') != NULL)
			break;
	}
}

char *get_next_line(int fd) {
	static char *acc[FD_LIMIT];
	char *buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	read_line(fd, &acc[fd], buffer);
	line = get_line(&acc[fd]);
	free(buffer);
	return (line);
}