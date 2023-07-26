#include "main.h"

/**
 * get_precision - calculate precision to be printed
 * @format: foramtted string to get precision
 * @i: list of argument
 * @args: argument to retrieve
 *
 * Return: precision
 */

int get_precision(const char *format, int *i, va_list args)
{
	int current_i = *i + 1;
	int precision = -1;

	if (format[current_i] != '.')
		return (precision);

	precision = 0;

	while (format[current_i] != '\0')
	{
		current_i++;

		if (is_digit(format[current_i]))
		{
			precision *= 10;
			precision += format[current_i] - '0';
		}
		else if (format[current_i] == '*')
		{
			current_i++;
			precision = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*i = current_i - 1;

	return (precision);
}
