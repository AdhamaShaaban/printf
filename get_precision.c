#include "main.h"

/**
 * _printf - print data to stdout according to a format.
 * @format: A string containing zero or more directives to print.
 *
 * Return: the number of characters printed (excluding the null byte
 * used to end output to strings).
 */
int _printf(const char *format, ...)
{
	va_list list;
	int i, j, len = 0;
	char *str;
	char c;

	va_start(list, format);

	for (i = 0; format && format[i]; i++)
	{
		if (format[i] != '%')
		{
			len += _putchar(format[i]);
			continue;
		}

		for (j = i + 1; format[j]; j++)
		{
			if (is_valid_specifier(format[j]))
				break;
			if (is_valid_flag(format[j]))
				continue;
			if (is_digit(format[j]) || format[j] == '*')
				break;
		}

		if (!format[j])
			return (-1);

		c = format[j];

		switch (c)
		{
			case 'c':
				len += print_char(format[i + 1], list);
				i = j;
				break;
			case 's':
				str = va_arg(list, char *);
				len += print_string(str, format, &i);
				i = j;
				break;
			case 'd':
			case 'i':
				len += print_number(format[i], c, list, format, &i);
				i = j;
				break;
			case 'u':
			case 'o':
			case 'x':
			case 'X':
				len += print_unsigned_number(format[i], c, list, format, &i);
				i = j;
				break;
			case '%':
				len += _putchar('%');
				i = j;
				break;
			default:
				len += print_unknown_specifier(format[i], c);
				i = j;
				break;
		}
	}

	va_end(list);

	return (len);
}
