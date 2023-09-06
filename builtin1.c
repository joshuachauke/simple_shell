#include "shell.h"

/**
 * _myhistory - History list should be displayed,
 * Line should be followed by one command,
 * Followed by line numbers, starting at 0.
 * @info: Struct engulfing potential arguments. Utilised in order to maintain
 *prototype with constant function.
 *  Return: 0 should be returned always
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias – Alias is set to a string
 * @info: The Parameter structure
 * @str: A string of an alias
 *
 * Return: 0 should be returned always on success,
 * On error the 1 should be returned
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Alias is set to a string
 * @info: The Parameter structure
 * @str: A string of an alias
 *
 * Return: On success 0 should always returned, On error return 1
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - An alias string is printed
 * @node: Node alias
 *
 * Return: On success 0 should always returned, On error return 1
 */
int print_alias(list_t *node)
{
	char *p = NULL, *b = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (b = node->str; b <= p; b++)
		_putchar(*b);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - copies alias Builtin
 * @info: Struct engulfing potential arguments. Utilised in order to maintain
 *prototype with constant function.
 *  Return: 0 should be returned always
 */
int _myalias(info_t *info)
{
	int t = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (t = 1; info->argv[t]; t++)
	{
		p = _strchr(info->argv[t], '=');
		if (p)
			set_alias(info, info->argv[t]);
		else
			print_alias(node_starts_with(info->alias, info->argv[t], '='));
	}

	return (0);
}

