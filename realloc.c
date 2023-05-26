#include "main.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - re allocates memory
 * @ptr: pointer
 * @old_size: old size
 * @new_size: new_size
 * Return: void pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *result = NULL;

	if (!ptr)
	{
		return (malloc(new_size));
	}
	if (new_size)
	{
		if (new_size == old_size)
		{
			return (ptr);
		}

		result = malloc(new_size);
		if (result)
		{
			if (old_size > new_size)
			memcpy(result, ptr, new_size);
			else if (new_size > old_size)
			memcpy(result, ptr, old_size);
			free(ptr);
		}
	}
	else
	{
		if (ptr)
		{
			free(ptr);
		}
	}
	return (result);
}
