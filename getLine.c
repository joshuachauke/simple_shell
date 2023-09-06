#include "shell.h"

/**
 * input_buf - Commands of buffers that are chained
 * @info: Parameter structure
 * @buf: Buffer address
 * @len: len variable address
 *
 * Return: Read bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		x = getline(buf, &len_p, stdin);
#else
		x = _getline(info, buf, &len_p);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0'; /* remove trailing newline */
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
}

/**
 * get_input - Minus the newline after getting a line
 * @info: Parameter structure
 *
 * Return:  Read bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t t, v, len;
	ssize_t x = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	x = input_buf(info, &buf, &len);
	if (x == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		v = t; /* init new iterator to current buf position */
		p = buf + t; /* get pointer for return */

		check_chain(info, buf, &v, t, len);
		while (v < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &v))
				break;
			v++;
		}

		t = v + 1; /* increment past nulled ';'' */
		if (t >= len) /* reached end of buffer? */
		{
			t = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (x); /* return length of buffer from _getline() */
}

/**
 * read_buf - buffer should be read
 * @info: Parameter structure
 * @buf: A buffer
 * @t: The size
 *
 * Return: x
 */
ssize_t read_buf(info_t *info, char *buf, size_t *t)
{
	ssize_t x = 0;

	if (*t)
		return (0);
	x = read(info->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*t = x;
	return (x);
}

/**
 * _getline – Should get the next line of an input from STDIN
 * @info: Parameter structure
 * @ptr: Pointer address to buffer, NULL or Preallocated
 * @length: Preallocated size of ptr buffer if is not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t t, len;
	size_t m;
	ssize_t x = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (t == len)
		t = len = 0;

	x = read_buf(info, buf, &len);
	if (x == -1 || (x == 0 && len == 0))
		return (-1);

	c = _strchr(buf + t, '\n');
	m = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + m : m + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + t, m - t);
	else
		_strncpy(new_p, buf + t, m - t + 1);

	s += m - t;
	t = m;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - ctrl-C is blocked
 * @sig_num: number of a signal
 *
 * Return: void must be returned
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("$ ");
	_puts("\n");
	_putchar(BUF_FLUSH);
}

