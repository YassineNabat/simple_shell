#include "shell.h"

void *_memcpy(void *dst, void *src, size_t n)
{
	char *destination;
	char *source;

	destination = (char *)dst;
	source = (char *)src;
	if (dst == src)
		return (dst);
	while (n > 0)
	{
		*destination = *source;
		destination++;
		source++;
		n--;
	}
	return (dst);
}

char *_strjoin(char *s1, char *s2)
{
	char *new_str;
	int size1;
	int size2;
	int size;

	size1 = strlen(s1);
	size2 = strlen(s2);
	size = size1 + size2;
	new_str = malloc(sizeof(char) * (size + 2));
	if (!new_str)
		return (NULL);
	if (!s1 || !s2)
		return (NULL);
	_memcpy(new_str, s1, size1);
	_memcpy(new_str + size1, "/", 1);
	_memcpy(new_str + size1 + 1, s2, size2);
	new_str[size + 1] = '\0';
	return (new_str);
}

int _strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char *search_path(char *env[])
{
	while (env && *env)
	{
		if (!_strncmp(*env, "PATH=", 5))
			return (*env);
		env++;
	}
	return (NULL);
}

char *_strchr(const char *s, int c)
{
	while (*s++)
		if (*s == (char)c)
			return ((char *)s);
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int is_directory(char *command)
{
	if (_strchr(command, '/') != NULL)
		if (!access(command, X_OK | F_OK))
			return (1);
	return (0);
}

char *path_of_command(char *env[], char *command)
{
	int i;
	char *path;
	char *holder;
	char **paths;

	if (is_directory(command))
		return (command);
	path = search_path(env);
	if (!path)
		return NULL;
	paths = split((path + 5), ':');
	if (!paths)
		return NULL;
	i = 0;
	while (paths && paths[i])
	{
		holder = _strjoin(paths[i], command);
		
		if (access(holder, X_OK | F_OK ) == 0)
		{
			i = -1;
			while (paths[++i])
				free(paths[i]);
			free(paths);
	
			return (holder);
		}
		free(holder);
		i++;
	}
	return ( NULL);
}

int main(int ac, char **av, char **env)
{
	while(1){
	write(1 ,"$ ", 2);
	char *line;
	char **splitted_cmd = split(line, ' ');
	char *cmd = splitted_cmd[0];
	char *path = path_of_command(env, cmd);
	(void)ac;
	(void)av;

	line = get_line(1);
	execve(path, splitted_cmd, NULL);
	

	}
	return 0;
}
