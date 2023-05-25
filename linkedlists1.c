#include "main.h"

/**
 * list_len - calcs length of linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t list_len(const liststr_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns array of linked list strings
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(liststr_t *head)
{
	liststr_t *node = head;
	size_t a = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < a; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list(const liststr_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - gets what node strts with
 * @node: pointer to list head
 * @prefix: string to match
 * @ch: the next character after prefix to match
 * Return: match node or null
 */
liststr_t *node_starts_with(liststr_t *node, char *prefix, char ch)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((ch == -1) || (*p == ch)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets index of node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(liststr_t *head, liststr_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
