#include "main.h"

/**
 * get_flags - get active flag
 * @format: formatted string to print the argument
 * @i: take parameter
 * Return: flags
 */

int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8 16 */

	int j, current_i;
	int flags = 0;

	const char flags_chars[] = {'-', '+', '0', '#', ' ', '\0'};
	const char flags_arr[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_i = *i + 1; format[current_i] != '\0'; current_i++)
	{
		for (j = 0; flags_chars[j] != '\0'; j++)
		{
			if (format[current_i] == flags_chars[j])
			{
				flags |= flags_arr[j];
				break;
			}
		}

		if (flags_chars[j] == 0)
			break;
	}

	*i = current_i - 1;

	return (flags);
}
