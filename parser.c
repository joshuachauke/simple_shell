#include "shell.h"

/**
 * is_cmd – Should determine if a file is an execut command
 * @info: Info structure
 * @path: File path
 *
 * Return: If true return 1, Otherwise return 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars – Should duplicate charac
 * @pathstr: String path
 * @start: Index that start
 * @stop: Index that stop
 *
 * Return: Pointer to new buf
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int t = 0, m = 0;

	for (m = 0, t = start; t < stop; t++)
		if (pathstr[t] != ':')
			buf[m++] = pathstr[t];
	buf[m] = 0;
	return (buf);
}

/**
 * find_path – Should find the cmd in the string path
 * @info: Info structure
 * @pathstr: String path
 * @cmd: cmd to be  found
 *
 * Return: Full path of cmd  should be returned if found or Null
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int t = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[t] || pathstr[t] == ':')
		{
			path = dup_chars(pathstr, curr_pos, t);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, cmd);
				_strcat(path, "/");
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[t])
				break;
			curr_pos = t;
		}
		t++;
	}
	return (NULL);
}

