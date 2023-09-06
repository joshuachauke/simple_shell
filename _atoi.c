#include "shell.h"

/**
 * interactive -  If Shell is interactive mode then true is returned
 * @info:  Structure of an address
 *
 * Return: If interactive mode 1 should be returned,
 * Otherwise 0 should be returned
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - If it's a character, the delimiter will be checked
 * @c: The char is to be checked
 * @delim: A delimeter string
 * Return:  if true then 1 should be returned, if false 0 to be returned
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha – Checks for alphabetic character
 * @c: input character
 * Return: If c is alphabetic then 1, Otherwise a 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi -  A string should be converted to an integer
 * @s: The converted string
 * Return: If no numbers in a string 0 should be return,
 * otherwise converted numbers should return
 */

int _atoi(char *s)
{
	int t, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (t = 0; s[t] != '\0' && flag != 2; t++)
	{
		if (s[t] == '-')
			sign *= -1;

		if (s[t] >= '0' && s[t] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[t] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

