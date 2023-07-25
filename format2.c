#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned number
 * @args: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */

int print_unsigned(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int n = va_arg(args, unsigned long int);

	n = convert_size_unsgnd(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[i--] = (n % 10) + '0';
		n /= 10;
	}

	i++;

	return (write_unsignd(0, i, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_octal(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int n = va_arg(args, unsigned long int);
	unsigned long int num_to_convert = n;

	UNUSED(width);
	n = convert_size_unsgnd(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE] = '\0';

	while (n > 0)
	{
		buffer[i--] = (n % 8) + '0';
		n /= 8;
	}

	if (flags & F_HASH && num_to_convert != 0)
		buffer[i--] = '0';
	i++;

	return (write_unsignd(0, i, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(args, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @args: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(args, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @args: Lista of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @flagCh: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */

int print_hexa(va_list args, char map_to[], char buffer[],
	int flags, char flagCh, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int n = va_arg(args, unsigned long int);
	unsigned long int num_to_convert = n;

	UNUSED(width);

	n = convert_size_unsgnd(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE] = '\0';

	while (n > 0)
	{
		buffer[i--] = map_to[n % 16];
		n /= 16;
	}

	if (flags & F_HASH && num_to_convert != 0)
	{
		buffer[i--] = flagCh;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsignd(0, i, buffer, flags, width, precision, size));
}
