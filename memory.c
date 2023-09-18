#include "shell.h"

/**
 * bfree -  Pointer is freed and should NULLs an address
 * @ptr: Pointer address to be freed
 *
 * Return: If freedreturn 1, Otherwise return 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

