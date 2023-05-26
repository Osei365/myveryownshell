#include "main.h"

/**
 * shellinteractive - returns true if the shell is in interactive
 * @arg: argument address
 *
 * Return: 1 else 0
 */
int interactive(arg_t *arg)
{
	return (isatty(STDIN_FILENO) && arg->readfd <= 2);
}

/**
 * is_delim - confirms delimiter
 * @ch: char
 * @delim: delimiter
 * Return: 1 else 0
 */
int is_delim(char ch, char *delim)
{
	for (; *delim; delim++)
		if (*delim == ch)
			return (1);
	return (0);
}

/**
 *_isalpha - confirms alpha characters
 *@ch: char
 *Return: 1 else 0
 */

int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@str:the string to be converted
 *Return: 0 if string contains no numbers
 */

int _atoi(char *str)
{
	int a, sn = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0;  str[a] != '\0' && flag != 2; a++)
	{
		if (str[a] == '-')
			sn *= -1;

		if (str[a] >= '0' && str[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sn == -1)
		output = -result;
	else
		output = result;

	return (output);
}
