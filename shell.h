#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_line.h"

typedef struct s_split
{
	char **matrice;
	int count;
	int i;
	int j;
}t_split;

	char *path_of_command(char *env[], char *command);
	char **split(char *s, char c);
	char *read_line(void);

#endif
