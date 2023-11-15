#include "shell.h"

char *_ncopy(char *d, char *s, size_t n)
{
	if(s)
	{
		while (n)
		{
			*d++ = *s++;
			n -= 1;
		}
		*d = '\0';
		return (d);
	}
	return (NULL);
}

char *_duplicate(char *s)
{
	size_t len;
	char *copy;

	if (s)
	{
		len = _strlen(s) ;
		copy = malloc(len + 1);
		if (copy)
		{
			copy = _ncopy(copy, s, len);
			return (copy);
		}
	}
	return (NULL);
}

size_t	_strlen(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
		return (i);
	}
	return (0);
}

char	*_search(char *s, char c)
{
	if (s && *s)
		while (*s++ != c)
			if (!*s)
				return 0;
	return (char *)s;
}

