#include "shell.h"

/**
 * get_environ - Copy of our environ string array is returned
 * @info: Struct engulfing potential arguments. Utilised in order to maintain
 *prototype with constant function
 * Return: 0 is always returned
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Environment variable is removed
 * @info: Struct engulfing potential arguments. Utilised in order to maintain
 *prototype with constant function.
 *  Return: On delete return 1, Otherwise return 0
 * @var:  Environment variable property of string
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t t = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), t);
			t = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		t++;
	}
	return (info->env_changed);
}

/**
 * _setenv - New environment var is initialized, Or an existing one is modified
 * @info: Struct engulfing potential arguments. Utilised in order to maintain
 *prototype with constant function.
 * @var: Environment variable property of string
 * @value: env variable value of string
 *  Return: 0 is always returned
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
