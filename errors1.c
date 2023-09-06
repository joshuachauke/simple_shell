#include "shell.h"

/**
 * _erratoi - A string is converted into an integer
 * @s: The converted  string
 * Return: If there are no num in string return 0,
 * Otherwise convert num, On error -1
 */
int _erratoi(char *s)
{
	int t = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (t = 0;  s[t] != '\0'; t++)
	{
		if (s[t] >= '0' && s[t] <= '9')
		{
			result *= 10;
			result += (s[t] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Error message is printed
 * @info: Return info structure and Parameter
 * @estr: String that contains a specified error type
 * Return If there are no numbers in string return 0,
 * Otherwise convert numbers, On error -1
 */

void print_error(info_t *info, char *estr)
{
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
}

/**
 * print_d - Decimal (int) number with (base 10),
 * will be printed by this function
 * @input: an Input
 * @fd: Write in filedescriptor
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int t, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (t = 1000000000; t > 1; t /= 10)
	{
		if (_abs_ / t)
		{
			__putchar('0' + current / t);
			count++;
		}
		current %= t;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - A clone of itoa should be converted as function
 * @num: the number
 * @base: A base
 * @flags: Flags of Argument
 *
 * Return: A string must be returned
 */
char *convert_number(long int num, int base, int flags)
{
	char *ptr;
	unsigned long n = num;

	static char *array;
	static char buffer[50];
	char sign = 0;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - First instance of '#' will be replaced with '\0'
 * @buf: String address to be modified
 *
 * Return:  0 to be returned always;
 */
void remove_comments(char *buf)
{
	int t;

	for (t = 0; buf[t] != '\0'; t++)
		if (buf[t] == '#' && (!t || buf[t - 1] == ' '))
		{
			buf[t] = '\0';
			break;
		}
}

