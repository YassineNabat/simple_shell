#include "shell.h"

#define BUFFER 1024

void	*_memcpy(void *dst, void *src, size_t n)
{
	char	*destination;
	char	*source;

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

char	*_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int	size1;
	int	size2;
	int	size;

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

int	_strncmp(char *s1, char *s2, size_t n)
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

char	*search_path(char *env[])
{
	while (env && *env)
	{
		if (!_strncmp(*env, "PATH=", 5))
			return (*env);
		env++;
	}
	return (NULL);
}

char	*_strchr(const char *s, int c)
{
	while (*s++)
		if (*s == (char)c)
			return ((char *)s);
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int	is_directory(char *command)
{
	if (_strchr(command, '/') != NULL)
		if (!access(command, X_OK | F_OK))
			return (1);
	return (0);
}

char *access_path(char *command, char **paths)
{
	int i;
	char *path;
	for (i = 0; paths[i]; i++)
	{
		path = malloc(strlen(paths[i]) + strlen(command) + 2);
		strcpy(path, paths[i]);
		strcat(path, "/");
		strcat(path, command);
		if (access(path, F_OK) == 0)
		{
			return path;
		}
		free(path);
	}
	return NULL;
}

char	*path_of_command(char *env[], char *command)
{
	char	*path;
	char	**paths;
	char *new;
	if (is_directory(command))
		return (command);
	path = search_path(env);
	if (!path)
		return NULL;
	paths = split((path + 5), ':');
	if (!paths)
		return NULL;
	new = access_path(command, paths);
	free(paths);
	if (new)
		return new;
	return ( NULL);
}

char	*read_line()
{
	char *buffer;
	size_t bufsize = 32;
	size_t characters;

	buffer = (char *)malloc(bufsize * sizeof(char));
	if (buffer)
		characters = getline(&buffer,&bufsize,stdin);
	return buffer;
}

int main(int ac, char **av, char **env)
{
	while(1)
	{
		write(1 ,"$ ", 2);
		char *line;
		char *path;
		line = read_line();
		char *p = strchr(line, '\n');
		if (p) *p = 0; 
		char **splitted_cmd = split(line, ' ');
		path = path_of_command(env, splitted_cmd[0]);
		if (!path)
			return (printf("error path not found"), 1);
		splitted_cmd[0] = path; 
		splitted_cmd[strlen(splitted_cmd[0]) + 1] = NULL;

		pid_t pid = fork();
		if (pid < 0) {
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) { 
			execve(path, splitted_cmd, env); 
			perror("execve"); 
			exit(EXIT_FAILURE);
		} else { 
			int status;
			waitpid(pid, &status, 0);
		}
	}
	return 0;
}
