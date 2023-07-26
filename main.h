#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/*Flags*/
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/*size*/
#ifdef __SIZEOF_LONG__
#define S_LONG __SIZEOF_LONG__
#else
#define S_LONG 2
#endif

#ifdef __SIZEOF_SHORT__
#define S_SHORT __SIZEOF_SHORT__
#else
#define S_SHORT 1
#endif

/**
 * struct fmt - struct
 *
 * @fmt: format
 * @func: function associated
 */

struct fmt
{
	char fmt;
	int (*func)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct format fmt_t - struct
 *
 * @format: format
 * @fmt_t: function associated
 */

typedef struct fmt fmt_t;

/*prototypes for printf functions*/
int _printf(const char *format, ...);
int handle_print(const char *fmt, int *index, va_list args, char buffer[],
	int flags, int width, int precision, int size);

/*Functions that handle other specifiers*/
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list args);
int get_precision(const char *format, int *i, va_list args);
int get_size(const char *format, int *i);

/********* FUNCTIONS ***************/

/* Funtions to print characters and strings */
int print_char(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_string(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_percent(va_list args, char buffer[],
	int flags, int width, int precision, int size);

/* Functions to print numbers */
int print_int(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_binary(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_unsigned(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_octal(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_hexadecimal(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_hexa_upper(va_list args, char buffer[],
	int flags, int width, int precision, int size);

int print_hexa(va_list args, char map_to[],
char buffer[], int flags, char flagCh, int width, int precision, int size);

/* Function to print non printable characters */
int print_non_printable(va_list args, char buffer[],
	int flags, int width, int precision, int size);

/* Funcion to print memory address */
int print_pointer(va_list args, char buffer[],
	int flags, int width, int precision, int size);
/*Function to print string in reverse*/
int print_reverse(va_list args, char buffer[],
	int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int print_rot13string(va_list args, char buffer[],
	int flags, int width, int precision, int size);

/* width handler */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int index, char buffer[],
	int flags, int width, int precision, int size);
int write_num(int ind, char buffer[],
        int flags, int width, int prec,
        int length, char padd, char extra_c);
int write_pointer(char buffer[], int index, int len,
        int width, int flags, char padd, char extra_c, int padd_start);

int write_unsignd(int is_negative, int index,
char buffer[],
	int flags, int width, int precision, int size);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);
#endif /*MAIN_H*/
