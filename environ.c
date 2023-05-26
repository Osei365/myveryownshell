#include "main.h"

/**
 * _myenv - displays current env
 * @arg: argument structure
 * Return: Always 0
 */
int _myenv(arg_t *arg)
{
	print_list_str(arg->envp);
	return (0);
}

/**
 * _getenv - gets env value
 * @arg: arg structure
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(arg_t *arg, const char *name)
{
	liststr_t *node = arg->envp;
	char *comp;

	for (; node; node = node->next)
	{
		comp = starts_with(node->str, name);
		if (comp && *comp)
			return (comp);
	}
	return (NULL);
}

/**
 * _mysetenv - sets a new env var
 * @arg: argument structure
 * Return: Always 0
 */
int _mysetenv(arg_t *arg)
{
	if (arg->ac != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(arg, arg->av[1], arg->av[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - unset env var
 * @arg: argument structure
 * Return: Always 0
 */
int _myunsetenv(arg_t *arg)
{
	int a;

	if (arg->ac == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= arg->ac; a++)
		_unsetenv(arg, arg->av[a]);

	return (0);
}

/**
 * populate_env_list - add to env list
 * @arg: argument structure
 * Return: Always 0
 */
int populate_env_list(arg_t *arg)
{
	liststr_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	arg->envp = node;
	return (0);
}
