#include "shell.h"

/**
 * is_chain - to see if the current char in the buf is a Chain delimeter.
 * @info: Parameter Structure
 * @buf: Character Buffer
 * @p: Current position address in buffer
 *
 * Return:  If chain delimeter return 1, Otherwise return 0
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t r = *p;

	if (buf[r] == '|' && buf[r + 1] == '|')
	{
		buf[r] = 0;
		r++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[r] == '&' && buf[r + 1] == '&')
	{
		buf[r] = 0;
		r++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[r] == ';') /* found end of this command */
	{
		buf[r] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = r;
	return (1);
}

/**
 * check_chain - depending on the previous status,
 * check if we should continue the chain.
 * @info: Parameter Structure
 * @buf: the char buffer
 * @p: Current position address in buffer
 * @s: Buffer beginning position
 * @len: Buffer Length
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t s, size_t len)
{
	size_t r = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[r] = 0;
			r = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[r] = 0;
			r = len;
		}
	}

	*p = r;
}

/**
 * replace_alias - In the tokenized string an aliases is replaced
 * @info: Parameter Structure
 *
 * Return: If replaced 1 should return, Otherwise return 0
 */
int replace_alias(info_t *info)
{
	int s;
	list_t *node;
	char *p;

	for (s = 0; s < 10; s++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - In tokenized string vars is replaced
 * @info: Parameter Structure
 *
 * Return: If replaced 1 should return, Otherwise return 0
 */
int replace_vars(info_t *info)
{
	int s = 0;
	list_t *node;

	for (s = 0; info->argv[s]; s++)
	{
		if (info->argv[s][0] != '$' || !info->argv[s][1])
			continue;

		if (!_strcmp(info->argv[s], "$?"))
		{
			replace_string(&(info->argv[s]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[s], "$$"))
		{
			replace_string(&(info->argv[s]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[s][1], '=');
		if (node)
		{
			replace_string(&(info->argv[s]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[s], _strdup(""));

	}
	return (0);
}

/**
 * replace_string – String replaced
 * @old: Old string address
 * @new: The string is new
 *
 * Return: If replaced 1 should return, Otherwise return 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

