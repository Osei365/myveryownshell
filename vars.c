#include "main.h"

/**
 * is_chain - checks for chain
 * @arg: argument struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(arg_t *arg, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		arg->cmd_buffer_type = COMMAND_O;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		arg->cmd_buffer_type = COMMAND_A;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		arg->cmd_buffer_type = COMMAND_C;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks chain
 * @arg: argument struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(arg_t *arg, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (arg->cmd_buffer_type == COMMAND_A)
	{
		if (arg->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (arg->cmd_buffer_type == COMMAND_O)
	{
		if (!arg->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces aliases
 * @arg: argument struct
 * Return: 1 or 0
 */
int replace_alias(arg_t *arg)
{
	int i;
	liststr_t *node;
	char *comp;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(arg->alias, arg->av[0], '=');
		if (!node)
			return (0);
		free(arg->av[0]);
		comp = _strchr(node->str, '=');
		if (!comp)
			return (0);
		comp = _strdup(comp + 1);
		if (!comp)
			return (0);
		arg->av[0] = comp;
	}
	return (1);
}

/**
 * replace_vars - replaces variables
 * @arg: arguments struct
 * Return: 1 or 0
 */
int replace_vars(arg_t *arg)
{
	int i = 0;
	liststr_t *node;

	for (i = 0; arg->av[i]; i++)
	{
		if (arg->av[i][0] != '$' || !arg->av[i][1])
			continue;

		if (!_strcmp(arg->av[i], "$?"))
		{
			replace_string(&(arg->av[i]),
				_strdup(convert_number(arg->status, 10, 0)));
			continue;
		}
		if (!_strcmp(arg->av[i], "$$"))
		{
			replace_string(&(arg->av[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(arg->envp, &arg->av[i][1], '=');
		if (node)
		{
			replace_string(&(arg->av[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&arg->av[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
