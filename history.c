#include "main.h"

/**
 * get_history_file - gets the history file
 * @arg: argument structure
 *
 * Return: pointer
 */

char *get_history_file(arg_t *arg)
{
	char *buffer, *dir;

	dir = _getenv(arg, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HFILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HFILE);
	return (buffer);
}

/**
 * write_history - write to the history
 * @arg: argument structure
 *
 * Return: 1 or -1
 */
int write_history(arg_t *arg)
{
	ssize_t fd;
	char *filename = get_history_file(arg);
	liststr_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = arg->hist; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FL, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @arg: argument structure
 *
 * Return: len of hist or 0
 */
int read_history(arg_t *arg)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = get_history_file(arg);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(arg, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(arg, buffer + last, linecount++);
	free(buffer);
	arg->histlen = linecount;
	while (arg->histlen-- >= HMAX)
		delete_node_at_index(&(arg->hist), 0);
	renumber_history(arg);
	return (arg->histlen);
}

/**
 * build_history_list - builds history linked list
 * @arg: argument structure
 * @buffer: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(arg_t *arg, char *buffer, int linecount)
{
	liststr_t *node = NULL;

	if (arg->hist)
		node = arg->hist;
	add_node_end(&node, buffer, linecount);

	if (!arg->hist)
		arg->hist = node;
	return (0);
}

/**
 * renumber_history - renumbers history linked list
 * @arg: argument structure
 *
 * Return: the new histcount
 */
int renumber_history(arg_t *arg)
{
	liststr_t *node = arg->hist;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (arg->histlen = i);
}
