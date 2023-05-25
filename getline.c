#include "main.h"

/**
 * input_buf - buffer
 * @arg: argument structure
 * @buffer: buffer
 * @len: len of buffer
 *
 * Return: bytes read
 */
ssize_t input_buf(arg_t *arg, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if GETLINE_AD
		r = getline(buffer, &len_p, stdin);
#else
		r = _getline(arg, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			arg->lc_flag = 1;
			remove_comments(*buffer);
			build_history_list(arg, *buffer, arg->histlen++);
			{
				*len = r;
				arg->cmd_buffer = buffer;
			}
		}
	}
	return (r);
}

/**
 * get_input - get input
 * @arg: argument structure
 *
 * Return: bytes read
 */
ssize_t get_input(arg_t *arg)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(arg->a), *p;

	_putchar(BUF_FL);
	r = input_buf(arg, &buffer, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		check_chain(arg, buffer, &j, i, len);
		while (j < len)
		{
			if (is_chain(arg, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			arg->cmd_buffer_type = COMMAND_N;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buffer;
	return (r);
}

/**
 * read_buf - reads buffer
 * @arg: argument structure
 * @buffer: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(arg_t *arg, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(arg->readfd, buffer, RD_BUF);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets line from standard input
 * @arg: argument strcuture
 * @ptr: pointer to buffer
 * @length: buffer size
 *
 * Return: s
 */
int _getline(arg_t *arg, char **ptr, size_t *length)
{
	static char buffer[RD_BUF];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *comp;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(arg, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	comp = _strchr(buffer + i, '\n');
	k = comp ? 1 + (unsigned int)(comp - buffer) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - alters CTRL + C
 * @sig_num: the signal number
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FL);
}
