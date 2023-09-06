#include "shell.h"

/**
 * _eputs - Input string is printed
 * @str:  String that need to be printed
 *
 * Return: none
 */
void _eputs(char *str)
{
	int t = 0;

	if (!str)
		return;
	while (str[t] != '\0')
	{
		_eputchar(str[t]);
		t++;
	}
}

/**
 * _eputchar - Character c is written to Stderr
 * @c: Printed Char
 * Return: 1 should be returned on success.
 * -1 on error, and appropriately set errno.
 */
int _eputchar(char c)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(2, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}

/**
 * _putfd - To bestowed fd, write Charc c
 * @c:  printed Charc
 * @fd: Write in filedescriptor
 * Return: 1 on Success. -1 on Error, and appropriately set errno.
 */
int _putfd(char c, int fd)
{
	static int t;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || t >= WRITE_BUF_SIZE)
	{
		write(fd, buf, t);
		t = 0;
	}
	if (c != BUF_FLUSH)
		buf[t++] = c;
	return (1);
}

/**
 * _putsfd - Input string is printed
 * @str: The printed string
 * @fd: Write in filedescriptor
 * Return: Chars put num
 */
int _putsfd(char *str, int fd)
{
	int t = 0;

	if (!str)
		return (0);
	while (*str)
	{
		t += _putfd(*str++, fd);
	}
	return (t);
}


