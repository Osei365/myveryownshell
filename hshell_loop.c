#include "main.h"

/**
 * hshell - main shell loop
 * @arg: argument structure
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hshell(arg_t *arg, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_arg(arg);
		if (shellinteractive(arg))
			_puts("$ ");
		_eputchar(BUF_FL);
		r = get_input(arg);
		if (r != -1)
		{
			set_arg(arg, av);
			builtin_ret = disc_builtin(arg);
			if (builtin_ret == -1)
				disc_cmd(arg);
		}
		else if (shellinteractive(arg))
			_putchar('\n');
		free_arg(arg, 0);
	}
	write_history(arg);
	free_arg(arg, 1);
	if (!shellinteractive(arg) && arg->status)
		exit(arg->status);
	if (builtin_ret == -2)
	{
		if (arg->err_no == -1)
			exit(arg->status);
		exit(arg->err_no);
	}
	return (builtin_ret);
}

/**
 * disc_builtin - discovers a builtin command
 * @arg: the parameter & return info struct
 *
 * Return: -1, 0, 1, or 2
 */
int disc_builtin(arg_t *arg)
{
	int i, built_in_ret = -1;
	blt_t builtintbl[] = {
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

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(arg->av[0], builtintbl[i].type) == 0)
		{
			arg->l_count++;
			built_in_ret = builtintbl[i].func(arg);
			break;
		}
	return (built_in_ret);
}

/**
 * disc_cmd - discovers cmd in path
 * @arg: arg struct
 *
 * Return: void
 */
void disc_cmd(arg_t *arg)
{
	char *path = NULL;
	int i, k;

	arg->path = arg->av[0];
	if (arg->lc_flag == 1)
	{
		arg->l_count++;
		arg->lc_flag = 0;
	}
	for (i = 0, k = 0; arg->a[i]; i++)
		if (!is_delim(arg->a[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = disc_path(arg, _getenv(arg, "PATH="), arg->av[0]);
	if (path)
	{
		arg->path = path;
		fork_cmd(arg);
	}
	else
	{
		if ((shellinteractive(arg) || _getenv(arg, "PATH=")
			|| arg->av[0][0] == '/') && check_cmd(arg, arg->av[0]))
			fork_cmd(arg);
		else if (*(arg->a) != '\n')
		{
			arg->status = 127;
			print_error(arg, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @arg: arg struct
 *
 * Return: void
 */
void fork_cmd(arg_t *arg)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(arg->path, arg->av, get_environ(arg)) == -1)
		{
			free_arg(arg, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(arg->status));
		if (WIFEXITED(arg->status))
		{
			arg->status = WEXITSTATUS(arg->status);
			if (arg->status == 126)
				print_error(arg, "Permission denied\n");
		}
	}
}
