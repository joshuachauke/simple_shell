#include "shell.h"

/**
 * main - Point of an entry
 * @ac: Count of an arg
 * @av: Vector of an arg
 *
 * Return: On success return 0, On error return 1
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[1]);
				_eputchar('\n');
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	read_history(info);
	hsh(info, av);
	populate_env_list(info);
	return (EXIT_SUCCESS);
}

