#include "shell.h"

/**
 **_strncpy - String to be copied
 *@dest: A destination  for the string to be copied into
 *@src: String Source
 *@n: Amount of charac to be copied
 *Return: String that is Concatenated
 */
char *_strncpy(char *dest, char *src, int n)
{
	int t, v;
	char *s = dest;

	t = 0;
	while (src[t] != '\0' && t < n - 1)
	{
		dest[t] = src[t];
		t++;
	}
	if (t < n)
	{
		v = t;
		while (v < n)
		{
			dest[v] = '\0';
			v++;
		}
	}
	return (s);
}

/**
 **_strncat - Two strings should be concatenated
 *@dest: First String
 *@src: Second String
 *@n: The amount of maximally utilised bytes
 *Return: String that is concatenated
 */
char *_strncat(char *dest, char *src, int n)
{
	int t, v;
	char *s = dest;

	t = 0;
	v = 0;
	while (dest[t] != '\0')
		t++;
	while (src[v] != '\0' && v < n)
	{
		dest[t] = src[v];
		t++;
		v++;
	}
	if (v < n)
		dest[t] = '\0';
	return (s);
}

/**
 **_strchr - Character in a string is located
 *@s: Parsed string
 *@c: Look for this character
 *Return: (s) A pointer that return the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
