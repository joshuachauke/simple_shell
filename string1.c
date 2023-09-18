#include "shell.h"

/**
 * _strcpy – mimics the string
 * @dest: buf destination
 * @src: buf source
 *
 * Return: should return pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int t = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[t])
	{
		dest[t] = src[t];
		t++;
	}
	dest[t] = 0;
	return (dest);
}

/**
 * _strdup – should duplicate the string
 * @str: Duplicated string
 *
 * Return: Should return pointer to a duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - Input string to be printed
 * @str: Printed string
 *
 * Return: Nothing should be returned
 */
void _puts(char *str)
{
	int t = 0;

	if (!str)
		return;
	while (str[t] != '\0')
	{
		_putchar(str[t]);
		t++;
	}
}

/**
 * _putchar – Should write character c to stdout
 * @c: Character to be printed
 *
 * Return: 1 should be returned on success. On error,
 * -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(1, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}

