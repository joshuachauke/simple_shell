#include "shell.h"

/**
 * _memset - Memory should be filled with a constant byte
 * @s: Pointer to the area of the memory
 * @b: A byte we should  fill *s with
 * @n: Amount of bytes to be filled
 * Return: (s) Pointer to the area of the memory s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int t;

	for (t = 0; t < n; t++)
		s[t] = b;
	return (s);
}

/**
 * ffree – Should free the string of strings
 * @pp: The string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc –Should reallocate a memory block
 * @ptr: Previous pointer of malloc'ated block
 * @old_size: Previous block byte size
 * @new_size: New block byte size
 *
 * Return: ol'block nameen pointer should be returned.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

