#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_list {
	char *content;
	int fd;
	struct s_list *next;
} t_list;

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

void ft_strupd(char **str, char *newstr) {
	char *temp;

	temp = *str;
	*str = newstr;
	free(temp);
}

size_t ft_strlcpy(char *dst, const char *src, size_t size) {
	size_t len_src;
	size_t i;

	len_src = strlen(src);
	if (size > 0) {
		i = 0;
		while (i < size - 1 && src[i] != '\0') {
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len_src);
}

char *ft_strjoin(char const *s1, char const *s2) {
	size_t ls1;
	size_t ls2;
	char *s;
	size_t i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ls1 = strlen(s1);
	ls2 = strlen(s2);
	s = (char *)malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (s == NULL)
		return (NULL);
	i = -1;
	while (++i < ls1)
		s[i] = s1[i];
	i = -1;
	while (++i < ls2)
		s[i + ls1] = s2[i];
	s[i + ls1] = '\0';
	return (s);
}

char *ft_substr(char const *s, unsigned int start, size_t len) {
	char *sub;
	size_t slen;
	size_t size;

	if (s == NULL)
		return (NULL);
	slen = strlen(s);
	if (start > slen)
		return (strdup(""));
	if (slen - start > len)
		size = len + 1;
	else
		size = slen - start + 1;
	sub = (char *)malloc(sizeof(char) * size);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, (s + start), size);
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
	ft_strupd(acc, r);
	if (*acc[0] == '\0')
		ft_strupd(acc, NULL);
	return (s);
}

static void read_line(int fd, char **acc, char *buffer, int *read_bytes) {
	*read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (*read_bytes > 0) {
		if (*acc == NULL)
			*acc = strdup("");
		buffer[*read_bytes] = '\0';
		ft_strupd(acc, ft_strjoin(*acc, buffer));
		while (*read_bytes > 0 && strchr(buffer, '\n') == NULL) {
			*read_bytes = read(fd, buffer, BUFFER_SIZE);
			buffer[*read_bytes] = '\0';
			ft_strupd(acc, ft_strjoin(*acc, buffer));
		}
	}
}

static t_list *get_node(t_list **lst, int fd) {
	t_list *node;
	t_list *new;

	node = *lst;
	if (node != NULL)
		while (node != NULL && node->fd != fd)
			node = node->next;
	if (node != NULL)
		return (node);
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = NULL;
	new->fd = fd;
	new->next = NULL;
	if (*lst == NULL)
		*lst = new;
	else {
		node = *lst;
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
	return (new);
}

static void free_acc(t_list **lst) {
	t_list *node;
	t_list *temp;

	node = *lst;
	while (node != NULL && node->content == NULL) {
		temp = node->next;
		free(node);
		node = temp;
	}
	*lst = node;
	while (node != NULL) {
		temp = node->next;
		if (temp != NULL && temp->content == NULL) {
			node->next = temp->next;
			free(temp);
		} else
			node = temp;
	}
}

char *get_next_line(int fd) {
	static t_list *acc = NULL;
	t_list *node;
	char *buffer;
	char *line;
	int read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node(&acc, fd);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	read_line(fd, &node->content, buffer, &read_bytes);
	line = get_line(&node->content);
	free(buffer);
	free_acc(&acc);
	return (line);
}