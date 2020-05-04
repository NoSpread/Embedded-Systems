#include "../include/Printf.h"
#include <cstdarg>

auto writeToBuffer(char* dst, const void* end, char* copy) -> char*
{
	while (dst < end && *copy != '\0')
	{
		*dst = *copy;
		dst++;
		copy++;
	}
	return dst;
}

template <typename T>
auto itoa(T value, char* result, int base) -> char*
{
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	auto ptr = result, ptr1 = result;
	T tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
	} while (value);

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';

	// Add 0x to Hex
	if (base == 16)
	{
		*ptr++ = 'x';
		*ptr++ = '0';
	}
	// Add 0b to Binary
	if (base == 2)
	{
		*ptr++ = 'b';
		*ptr++ = '0';
	}
	
	*ptr-- = '\0';
	while (ptr1 < ptr) {
		const auto tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}


auto Printf(char* dst, const void* end, const char* fmt, ...) -> char*
{
	if (dst == nullptr || end == nullptr || fmt == nullptr || dst >= end) {
		return nullptr;
	}
	
	va_list argumentList;
	va_start(argumentList, fmt);
	auto lastOperator = false;
	char buffer[300];
	const auto p_start = dst;

    union Printable_t {
        int			    d;
        unsigned int    u;
        char            c;
        char*           s;
    } Printable{};

    while (dst < end && *fmt != '\0')
    {
        if (*fmt == '%')
        {
	        if (lastOperator)
	        {
				*dst = '%';
				dst++;
				lastOperator = false;
	        } else
	        {
				lastOperator = true;
	        }
        } else {
			if (lastOperator)
			{
				switch (*fmt)
				{
				case 'd':
					Printable.d = va_arg(argumentList, int);
					dst = writeToBuffer(dst, end, itoa(Printable.d, buffer, 10));
					break;
				case 'u':
					Printable.u = va_arg(argumentList, unsigned int);
					dst = writeToBuffer(dst, end, itoa(Printable.u, buffer, 10));
					break;
				case 'c':
					Printable.c = va_arg(argumentList, int);
					*dst = Printable.c;
					dst++;
					break;
				case 's':
					Printable.s = va_arg(argumentList, char*);
					dst = writeToBuffer(dst, end, Printable.s);
					break;
				case 'x':
					Printable.u = va_arg(argumentList, int);
					dst = writeToBuffer(dst, end, itoa(Printable.u, buffer, 16));
					break;
				case 'b':
					Printable.u = va_arg(argumentList, int);
					dst = writeToBuffer(dst, end, itoa(Printable.u, buffer, 2));
					break;
				default:
					return nullptr;
				}
				lastOperator = false;
			} else
			{
				*dst = *fmt;
				dst++;
			}
        }
		fmt++;
    }

	*dst = '\0';
	va_end(argumentList);
	
	return p_start;
}
