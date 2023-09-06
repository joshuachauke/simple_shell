#include "shell.h"

/**
 * _myenv - Current environment is printed
 * @info: Struct engulfing potential arguments. Utilised in order to maintain
 *prototype with constant function.
 * Return: 0 should be returned always
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Gets a variable's value in the environment
 * @info: Struct engulfing potential arguments. Utilised in order to maintain
 *prototype with constant function
 * @name: Name of environment variable
 * Return: Value must be returned
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Set up a new environment variable,
 * or alter one that already exists
 * @info: Struct engulfing potential arguments. Utilised in order to maintain,
 * prototype with constant function.
 * noReturn:  0 must always be returned
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - environment var should be removed
 * @info: Struct engulfing potential arguments. Utilised in order to maintain
 *prototype with constant function
 * Return: 0 must always be returned
 */
int _myunsetenv(info_t *info)
{
	int t;

	if (info->argc == 1)
	{
		_eputs("too few arguements.\n");
		return (1);
	}
	for (t = 1; t <= info->argc; t++)
		_unsetenv(info, info->argv[t]);

	return (0);
}

/**
 * populate_env_list - Environment linked list is populated
 * @info Struct engulfing potential arguments.
 * Utilised in order to maintain, prototype with constant function
 * Return: 0 must always be returned
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t t;

	for (t = 0; environ[t]; t++)
		add_node_end(&node, environ[t], 0);
	info->env = node;
	return (0);
}

