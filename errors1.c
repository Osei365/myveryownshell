#include "main.h"

/**
 * _erratoi - conv str to int
 * @s: string
 * Return: 0 or -1
 */
int _erratoi(char *s)
{
	int a = 0;
	unsigned long int output = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			output *= 10;
			output += (s[a] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * print_error - displays error message
 * @arg: argument structure
 * @estr: error string
 * Return: 0 and -1
 */
void print_error(arg_t *arg, char *estr)
{
	_eputs(arg->fn);
	_eputs(": ");
	print_d(arg->l_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(arg->av[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints base 10
 * @input: input
 * @fd: file descriptor
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	a = 1000000000;
	while (a > 1)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
			count++;
		}
		current %= a;
		a /= 10;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converts str to num
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buf[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & UN_CONVERT) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = flags & LC_CONVERT ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buf[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - removes comments
 * @bufffer: buffer address
 *
 * Return: Always 0;
 */
void remove_comments(char *buffer)
{
	int a;

	a = 0;
	while (buffer[a] != '\0')
	{
		if (buffer[a] == '#' && (!a || buffer[a - 1] == ' '))
		{
			buffer[a] = '\0';
			break;
		}
		a++;
	}
}
