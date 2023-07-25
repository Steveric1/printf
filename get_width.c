#include "main.h"

/**
 * get_width - calculate width for printing
 * @format: formatted string
 * @i: list of argument to print
 * @args: list of argument
 *
 * Return: width
 */

int get_width(const char *format, int *i, va_list args)
{
	int curr_i = *i + 1;
	int width = 0;

	while (format[curr_i] != '\0')
	{
		curr_i++;

		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (width);
}
