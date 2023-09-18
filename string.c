#include "shell.h"

/**
 * _strlen – Should return the length of a string
 * @s: String whose length to be checked
 *
 * Return: An integer length of string should be returned
 */
int _strlen(char *s)
{
	int t = 0;

	if (!s)
		return (0);

	while (*s++)
		t++;
	return (t);
}

/**
 * _strcmp – Should perform lexicogarphic comparison for two strings.
 * @s1: First string
 * @s2: Second string
 *
 * Return: Negative should return if s1 < s2,
 * Positive should retuen if s1 > s2, 0 if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Needle starting with haystack should be checked
 * @haystack: searching string
 * @needle: Substring to be found
 *
 * Return: Next char address of haystack  should return or Null
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - two strings should be concatenated
 * @dest: buf destination
 * @src: buf source
 *
 * Return: Should return pointer to destination buf
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

