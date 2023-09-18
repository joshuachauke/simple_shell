#include "shell.h"

/**
 * hsh - Shell loop main
 * @info: Parameter & return information structure
 * @av: an arg vector from main()
 *
 * Return: On success return 0, On error return 1, or return error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t t = 0;
	int builtin_ret = 0;

	while (t != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		t = get_input(info);
		if (t != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - builtin command should be found
 * @info: Parameter and return information structure
 *
 * Return: If builtin not found return -1,
 * If builtin executed successfully return 0,
 * If builtin found but not successful return 1,
 * If builtin signals exit() then return 2
 */
int find_builtin(info_t *info)
{
	int t, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (t = 0; builtintbl[t].type; t++)
		if (_strcmp(info->argv[0], builtintbl[t].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[t].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - In PATH a command should be found
 * @info: Parameter and return information structure
 *
 * Return: Void should be returned
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int t, m;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (t = 0, m = 0; info->arg[t]; t++)
		if (!is_delim(info->arg[t], " \t\n"))
			m++;
	if (!m)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd – Should fork a an executable thread to run cmd
 * @info: Parameter and return information structure
 *
 * Return: Void should be returned
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

