#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @args: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int print_pointer(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_s = 0, padd = ' ';
	int i = BUFF_SIZE - 2, len = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_address;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(args, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)addrs;

	while (num_address > 0)
	{
		buffer[i--] = map_to[num_address % 16];
		num_address /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_s = '+', len++;
	else if (flags & F_SPACE)
		extra_s = ' ', len++;

	i++;

	return (write_pointer(buffer, i, len,
		width, flags, padd, extra_s, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_non_printable(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int index = 0, offset = 0;
	char *str = va_arg(args, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[index] != '\0')
	{
		if (is_printable(str[index]))
			buffer[index + offset] = str[index];
		else
			offset += append_hexa_code(str[index], buffer, index + offset);
		index++;
	}

	buffer[index + offset] = '\0';

	return (write(1, buffer, index + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, j, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(args, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (j = 0; str[j]; j++)
		;

	for (i = j - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Print a string in rot13.
 * @args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_rot13string(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char y;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(args, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				y = out[j];
				write(1, &y, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			y = str[i];
			write(1, &y, 1);
			count++;
		}
	}
	return (count);
}
