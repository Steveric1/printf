#include "main.h"

void print_buffer(char *buffer, int *index);

/**
 * _printf - printf function
 * @format: format specifiers
 * Return: printed characters
 */

int _printf(const char *format, ...){
	int i, printed = 0, printed_characters = 0;
	int precision, width, size, flags, buffer_index = 0;
	va_list args;

	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffer_index++] = format[i];

			if (buffer_index == BUFF_SIZE)
				print_buffer(buffer, &buffer_index);
			printed_characters++;
		}
		else
		{
			print_buffer(buffer, &buffer_index);
			flags = get_flags(format, &i);
			width = get_width(format, &i, args);
			precision = get_precision(format, &i, args);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, args, buffer,
					flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_characters += printed;
		}
	}

	print_buffer(buffer, &buffer_index);

	va_end(args);
	return (printed_characters);
}

/**
 * print_buffer - print the characters in the buffer
 * @buffer: Arary of chars
 * @index: index of the characters
 */

void print_buffer(char *buffer, int *index){
	if (*index > 0)
		write(1, buffer, *index);
	index = 0;
}
