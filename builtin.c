#include "main.h"

/**
 * _myexit - exits shell
 * @arg: the argument structure
 * Return: exit with the status passed
 */
int _myexit(arg_t *arg)
{
	int check;

	if (arg->av[1])
	{
		check = _erratoi(arg->av[1]);
		if (check == -1)
		{
			arg->status = 2;
			print_error(arg, "Illegal number: ");
			_eputs(arg->av[1]);
			_eputchar('\n');
			return (1);
		}
		arg->err_no = _erratoi(arg->av[1]);
		return (-2);
	}
	arg->err_no = -1;
	return (-2);
}

/**
 * _mycd - cd builtin
 * @arg: argument structure
 *  Return: Always 0
 */
int _mycd(arg_t *arg)
{
	char *str, *dir, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!arg->av[1])
	{
		dir = _getenv(arg, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(arg, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(arg->av[1], "-") == 0)
	{
		if (!_getenv(arg, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(arg, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(arg, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(arg->av[1]);
	if (chdir_ret == -1)
	{
		print_error(arg, "can't cd to ");
		_eputs(arg->av[1]), _eputchar('\n');
	}
	else
	{
		_setenv(arg, "OLDPWD", _getenv(arg, "PWD="));
		_setenv(arg, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - help builtin
 * @arg: argument structure
 * Return: Always 0
 */
int _myhelp(arg_t *arg)
{
	char **arg_arr;

	arg_arr = arg->av;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temp att_unused workaround */
	return (0);
}
