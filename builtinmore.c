#include "main.h"

/**
 * _myhistory - displays history
 * @arg: argument structure
 * Return: Always 0
 */
int _myhistory(arg_t *arg)
{
	print_list(arg->hist);
	return (0);
}

/**
 * unset_alias - converts to string
 * @arg: argument structure
 * @s: string
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(arg_t *arg, char *s)
{
	char *comp, ch;
	int ret;

	comp = _strchr(s, '=');
	if (!comp)
		return (1);
	ch = *comp;
	*comp = 0;
	ret = delete_node_at_index(&(arg->alias),
		get_node_index(arg->alias, node_starts_with(arg->alias, s, -1)));
	*comp = ch;
	return (ret);
}

/**
 * set_alias - sets alias
 * @arg: parameter struct
 * @s: the string
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(arg_t *arg, char *s)
{
	char *comp;

	comp = _strchr(s, '=');
	if (!comp)
		return (1);
	if (!*++comp)
		return (unset_alias(arg, s));

	unset_alias(arg, s);
	return (add_node_end(&(arg->alias), s, 0) == NULL);
}

/**
 * print_alias - prints alias
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(liststr_t *node)
{
	char *comp = NULL, *a = NULL;

	if (node)
	{
		comp = _strchr(node->str, '=');
		for (a = node->str; a <= comp; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(comp + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - alias builtin
 * @arg: argument structure
 * Return: Always 0
 */
int _myalias(arg_t *arg)
{
	int a = 0;
	char *comp = NULL;
	liststr_t *node = NULL;

	if (arg->ac == 1)
	{
		node = arg->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; arg->av[a]; a++)
	{
		comp = _strchr(arg->av[a], '=');
		if (comp)
			set_alias(arg, arg->av[a]);
		else
			print_alias(node_starts_with(arg->alias, arg->av[a], '='));
	}

	return (0);
}
