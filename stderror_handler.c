#include "main.h"

/**
 *_eputs - displays string input
 * @s: string to be displayed
 */
void _eputs(char *s)
{
	int a = 0;

	if (!s)
		return;
	for (; s[a] != '\0'; a++)
	{
		_eputchar(s[a]);
	}
}

/**
 * _eputchar - putchar ch to standard error
 * @ch: char
 *
 * Return: 1 or 2
 */
int _eputchar(char ch)
{
	static int a;
	static char buffer[WR_BUF];

	if (ch == BUF_FL || a >= WR_BUF)
	{
		write(2, buffer, a);
		a = 0;
	}
	if (ch != BUF_FL)
		buffer[a++] = ch;
	return (1);
}

/**
 * _putfd - writes ch to file descriptor
 * @ch: char
 * @fd: file descriptor
 *
 * Return: 1 or 0
 */
int _putfd(char ch, int fd)
{
	static int a;
	static char buffer[WR_BUF];

	if (ch == BUF_FL || a >= WR_BUF)
	{
		write(fd, buffer, a);
		a = 0;
	}
	if (ch != BUF_FL)
		buffer[a++] = ch;
	return (1);
}

/**
 *_putsfd - prints input str to fd
 * @s: str
 * @fd: file descriptor
 *
 * Return: len of chars
 */
int _putsfd(char *s, int fd)
{
	int a = 0;

	if (!s)
		return (0);
	for (; *s; s++)
	{
		a += _putfd(*s, fd);
	}
	return (a);
}
