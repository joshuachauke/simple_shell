#include "shell.h"

/**
 * _myexit - The shell is exited
 * @info: Struct engulfing potential arguments.
 * Utilised in order to maintain, prototype with constant function.
 * Return: Exits with a bestowed exit status
 * (0) if information.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* if there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd – Switches the current process directory
 * @info: Struct engulfing potential arguments.
 * Utilised in order to maintain, prototype with constant function.
 * Return: 0 should be returned always
 */
int _mycd(info_t *info)
{
	char *b, *dir, buffer[1024];
	int chdir_ret;

	b = getcwd(buffer, 1024);
	if (!b)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: What should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(b);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: What should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "Cannot cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Switches the current process directory
 * @info: Struct engulfing potential arguments.
 * Utilised in order to maintain, prototype with constant function.
 * Return: 0 should be returned always
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Help call works. function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* Temp att_unused workaround */
	return (0);
}
