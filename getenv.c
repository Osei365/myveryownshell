#include "main.h"

/**
 * get_environ - gets copy of environ
 * @arg: argument structure
 * Return: Always 0
 */
char **get_environ(arg_t *arg)
{
	if (!arg->environ || arg->env_ch)
	{
		arg->environ = list_to_strings(arg->envp);
		arg->env_ch = 0;
	}

	return (arg->environ);
}

/**
 * _unsetenv - un set env var
 * @arg: argument structure
 * @var: the string env var property
 * Return: 1 or 0
 */
int _unsetenv(arg_t *arg, char *var)
{
	liststr_t *node = arg->envp;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			arg->env_ch = delete_node_at_index(&(arg->envp), i);
			i = 0;
			node = arg->envp;
			continue;
		}
		node = node->next;
		i++;
	}
	return (arg->env_ch);
}

/**
 * _setenv - iableset env var
 * @arg: Argument structure
 * @var: env var
 * @value: env var value
 * Return: Always 0
 */
int _setenv(arg_t *arg, char *var, char *value)
{
	char *buffer = NULL;
	liststr_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = arg->envp;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			arg->env_ch = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(arg->envp), buffer, 0);
	free(buffer);
	arg->env_ch = 1;
	return (0);
}
