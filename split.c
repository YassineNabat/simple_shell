#include "shell.h"

char *substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t length;
	size_t i;

	length = _strlen(s);
	i = 0;
	if (s)
	{
		if (start > length)
			length = 0;
		if (len > length && len)
			len = length;
		if (length <= start + len && len)
			len = length - start;
		sub = (char *)malloc((len + 1) * sizeof(char));
		if (sub)
		{
			while (i < len)
				sub[i++] = s[start++];
			sub[i] = '\0';
		}
		return (sub);
	}
	return (NULL);
}

static void _free(char **matrice, int last)
{
	int i;

	i = 0;
	while (i < last)
		free(matrice[i++]);
	free(matrice);
	matrice = (NULL);
}

static int _strdlen(const char *s, char d)
{
	int i;

	i = 0;
	while (*(s + i) != d && *(s + i))
		i++;
	return (i);
}

static int _wordcount(const char *s, char c)
{
	int count;
	int len;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		len = _strdlen(s, c);
		if (len)
		{
			count++;
			s += len;
		}
	}
	return (count);
}

char **split(char *s, char c)
{
	t_split	sp;

	sp.count = _wordcount(s, c);
	sp.matrice = (char **)malloc((sp.count + 1) * sizeof(char *));
	if (sp.matrice)
	{
		sp.i = 0;
		while (sp.i < sp.count)
		{
			if (*s != c && *s)
			{
				sp.j = _strdlen(s, c);
				*(sp.matrice + sp.i) = substr(s, 0, sp.j);
				if (!*(sp.matrice + sp.i))
					return (_free(sp.matrice, sp.i), NULL);
				s = s + sp.j;
				sp.i++;
			}
			else
				s++;
		}
		*(sp.matrice + sp.i) = NULL;
	}
	return (sp.matrice);
}
