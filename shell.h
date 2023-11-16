#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "get_line.h"

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);

typedef struct s_split
{
	char	**matrice;
	int	count;
	int	i;
	int	j;
}t_split;

char    *path_of_command(char *env[], char *command);
char    **split(char *s, char c);

#endif
