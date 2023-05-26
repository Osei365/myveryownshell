#include "main.h"

/**
 * clear_info - init argument structure
 * @arg: argument structure
 */
void clear_info(arg_t *arg)
{
	arg->a = NULL;
	arg->av = NULL;
	arg->path = NULL;
	arg->ac = 0;
}

/**
 * set_info - initialize argument structure
 * @arg: argument structure
 * @av: argument vector
 */
void set_info(arg_t *arg, char **av)
{
	int i = 0;

	arg->fn = av[0];
	if (arg->a)
	{
		arg->av = strtow(arg->a, " \t");
		if (!arg->av)
		{

			arg->av = malloc(sizeof(char *) * 2);
			if (arg->av)
			{
				arg->av[0] = _strdup(arg->a);
				arg->av[1] = NULL;
			}
		}
		for (i = 0; arg->av && arg->av[i]; i++)
			;
		arg->ac = i;

		replace_alias(arg);
		replace_vars(arg);
	}
}

/**
 * free_info - frees arg_t structure
 * @arg: argument address
 * @all: true if freeing all fields
 */
void free_info(arg_t *arg, int all)
{
	ffree(arg->av);
	arg->av = NULL;
	arg->path = NULL;
	if (all)
	{
		if (!arg->cmd_buffer)
			free(arg->a);
		if (arg->envp)
			free_list(&(arg->envp));
		if (arg->hist)
			free_list(&(arg->hist));
		if (arg->alias)
			free_list(&(arg->alias));
		ffree(arg->environ);
			arg->environ = NULL;
		bfree((void **)arg->cmd_buffer);
		if (arg->readfd > 2)
			close(arg->readfd);
		_putchar(BUF_FL);
	}
}
