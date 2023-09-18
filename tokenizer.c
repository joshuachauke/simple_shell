#include "shell.h"

/**
 * **strtow - String is divided into words. Ignore repeat delimiters
 * @str: Input String
 * @d: Delimeter String
 * Return: A pointer is returned to an array of strings, On failure return NULL
 */

char **strtow(char *str, char *d)
{
	int t, v, a, b, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (t = 0; str[t] != '\0'; t++)
		if (!is_delim(str[t], d) && (is_delim(str[t + 1], d) || !str[t + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (t = 0, v = 0; v < numwords; v++)
	{
		while (is_delim(str[t], d))
			t++;
		a = 0;
		while (!is_delim(str[t + a], d) && str[t + a])
			a++;
		s[v] = malloc((a + 1) * sizeof(char));
		if (!s[v])
		{
			for (a = 0; a < v; a++)
				free(s[a]);
			free(s);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			s[v][b] = str[t++];
		s[v][b] = 0;
	}
	s[v] = NULL;
	return (s);
}

/**
 * **strtow2 - separate the string into words
 * @str: String input
 * @d: Delimeter
 * Return: Pointer to an array of the strings should be returned,
 * or On failure return NULL
 */
char **strtow2(char *str, char d)
{
	int t, v, a, b, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (t = 0; str[t] != '\0'; t++)
		if ((str[t] != d && str[t + 1] == d) ||
				    (str[t] != d && !str[t + 1]) || str[t + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (t = 0, v = 0; v < numwords; v++)
	{
		while (str[t] == d && str[t] != d)
			t++;
		a = 0;
		while (str[t + a] != d && str[t + a] && str[t + a] != d)
			a++;
		s[v] = malloc((a + 1) * sizeof(char));
		if (!s[v])
		{
			for (a = 0; a < v; a++)
				free(s[a]);
			free(s);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			s[v][b] = str[t++];
		s[v][b] = 0;
	}
	s[v] = NULL;
	return (s);
}

