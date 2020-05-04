#ifndef PREALLOCSTRING_H
#define PREALLOCSTRING_H

#define CREATE(varName, size) PreAllocString<size> varName
#include <cstdarg>
#include "Printf.h"

template <size_t size>
class PreAllocString
{
public:
	operator const char*() const;
	operator const void*() const;
	const char& operator [](int idx);

	/* Current number of characters in string */
	size_t GetLength() const;

	/* Maximum number of characters possible */
	constexpr size_t SizeOf();

	/* Empty the string , set length field to zero */
	void Empty();

	PreAllocString& operator =(char rhs);
	PreAllocString& operator =(const char* rhs);
	PreAllocString& operator =(char* rhs);

	PreAllocString& operator +=(char rhs);
	PreAllocString& operator +=(char const* rhs);

	void AddFormat(const char* format, ...);
	void AddWhiteSpace();

private:
	char string[size]{'\0'};
};


template <size_t size>
PreAllocString<size>::operator const char*() const
{
	return this->string;
}

template <size_t size>
PreAllocString<size>::operator const void*() const
{
	return static_cast<const void*>(this->string);
}

template <size_t size>
const char& PreAllocString<size>::operator[](const int idx)
{
	if (static_cast<unsigned int>(idx) < size && idx >= 0)
		return string[idx];

	return string[0];
}

template <size_t size>
size_t PreAllocString<size>::GetLength() const
{
	size_t len = 0;
	while (string[len] != '\0' && len < size)
		len++;

	return len;
}

template <size_t size>
constexpr size_t PreAllocString<size>::SizeOf()
{
	return size;
}

template <size_t size>
void PreAllocString<size>::Empty()
{
	string[0] = '\0';
}

template <size_t size>
PreAllocString<size>& PreAllocString<size>::operator=(char rhs)
{
	if (size > 1)
	{
		string[0] = rhs;
		string[1] = '\0';
	}

	return *this;
}

template <size_t size>
PreAllocString<size>& PreAllocString<size>::operator=(char* const rhs)
{
	*this = static_cast<const char*>(rhs);
	return *this;
}

template <size_t size>
PreAllocString<size>& PreAllocString<size>::operator=(const char* rhs)
{
	unsigned int i = 0;
	while (rhs[i] != '\0' && i < size - 1)
	{
		string[i] = rhs[i];
		i++;
	}

	return *this;
}

template <size_t size>
PreAllocString<size>& PreAllocString<size>::operator+=(char rhs)
{
	size_t len = this->GetLength();

	if (len < size - 1)
	{
		string[len] = rhs;
		string[len + 1] = '\0';
	}

	return *this;
}

template <size_t size>
PreAllocString<size>& PreAllocString<size>::operator+=(char const* rhs)
{
	size_t len = this->GetLength();
	size_t i = 0;

	while (rhs[i] != '\0' && len < size - 1)
	{
		string[len] = rhs[i];
		++i;
		++len;
	}

	string[len] = '\0';

	return *this;
}

template <size_t size>
void PreAllocString<size>::AddFormat(const char* format, ...)
{
	va_list argumentList;
	va_start(argumentList, format);
	size_t len = GetLength();
	vPrintf(&string[len], &string[size - 1], format, argumentList);
	va_end(argumentList);
}

template <size_t size>
void PreAllocString<size>::AddWhiteSpace()
{
	*this += ' ';
}

#endif
