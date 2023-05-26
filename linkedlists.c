#include "main.h"

/**
 * add_node - adds node to beginning of node
 * @head: head of linked list
 * @str: string content
 * Return: (new head)
 */
liststr_t *add_node(liststr_t **head, const char *str, int num)
{
	liststr_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(liststr_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(liststr_t));
	new_head->n = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds node to end
 * @head: head of node
 * @str: string content in node
 * Return: the address of new node
 */
liststr_t *add_node_end(liststr_t **head, const char *str, int num)
{
	liststr_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(liststr_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(liststr_t));
	new_node->n = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints string element of linked list
 * @h: pointer to first node
 *
 * Return: size of linked list
 */
size_t print_list_str(const liststr_t *h)
{
	size_t i = 0;

	for (; h; i++, h = h->next)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
	}
	return (i);
}

/**
 * delete_nodeint_at_index - deletes node at index
 * @head: head of linked list
 * @index: index of linked list
 * Return: 1 or -1 as the case may be
 */
int delete_node_at_index(liststr_t **head, unsigned int index)
{
	liststr_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 * Return: void
 */
void free_list(liststr_t **head_ptr)
{
	liststr_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
