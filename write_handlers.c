#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: character types.
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @index: char types.
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */

int write_number(int is_negative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - index - 1;
	char padding = ' ', extra_cha = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_cha = '-';
	else if (flags & F_PLUS)
		extra_cha = '+';
	else if (flags & F_SPACE)
		extra_cha = ' ';

	return (write_num(index, buffer, flags, width, precision,
		len, padding, extra_cha));
}
/**
 * write_num - Write a number using a bufffer
 * @i: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @precision: Precision specifier
 * @len: Number length
 * @padding: Pading char
 * @extra_char: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int i, char buffer[],
	int flags, int width, int precision,
	int len, char padding, char extra_char)
{
	int j, padd_start = 1;

	if (precision == 0 && i == BUFF_SIZE - 2 && buffer[i] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precision == 0 && i == BUFF_SIZE - 2 && buffer[i] == '0')
		buffer[i] = padding = ' '; /* width is displayed with padding ' ' */
	if (precision > 0 && precision < len)
		padding = ' ';
	while (precision > len)
		buffer[--i] = '0', len++;
	if (extra_char != 0)
		len++;
	if (width > len)
	{
		for (j = 1; j < width - len + 1; j++)
			buffer[j] = padding;
		buffer[j] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			if (extra_char)
				buffer[--i] = extra_char;
			return (write(1, &buffer[i], len) + write(1, &buffer[1], j - 1));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			if (extra_char)
				buffer[--i] = extra_char;
			return (write(1, &buffer[1], j - 1) + write(1, &buffer[i], len));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			return (write(1, &buffer[padd_start], j - padd_start) +
				write(1, &buffer[i], len - (1 - padd_start)));
		}
	}
	if (extra_char)
		buffer[--i] = extra_char;
	return (write(1, &buffer[i], len));
}
/**
 * write_unsignd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsignd(int is_negative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int len = BUFF_SIZE - index - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < len)
		padd = ' ';

	while (precision > len)
	{
		buffer[--index] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > len)
	{
		for (i = 0; i < width - len; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[index], len) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], len));
		}
	}

	return (write(1, &buffer[index], len));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @index: Index at which the number starts in the buffer
 * @len: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @padding: Char representing the padding
 * @extra_char: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int index, int len,
	int width, int flags, char padding, char extra_char, int padd_start)
{
	int i;

	if (width > len)
	{
		for (i = 3; i < width - len + 3; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[index], len) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], len));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[index], len - (1 - padd_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extra_char)
		buffer[--index] = extra_char;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}
