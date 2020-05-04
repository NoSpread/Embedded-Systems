#ifndef SIEBEN_SEGMENT_H
#define SIEBEN_SEGMENT_H

template <typename... Args>
class MultiDigit
{
public:
	operator const char*() const;
	constexpr MultiDigit(Args ...args);

private:
	char string[sizeof...(Args) * 20 + 1];
	int digits[sizeof...(Args)];

	const char numbers[10][5][3] = {
		{
			{' ', '-', ' '},
			{'|', ' ', '|'},
			{' ', ' ', ' '},
			{'|', ' ', '|'},
			{' ', '-', ' '}
		},
		{
			{' ', ' ', ' '},
			{' ', ' ', '|'},
			{' ', ' ', ' '},
			{' ', ' ', '|'},
			{' ', ' ', ' '}
		},
		{
			{' ', '-', ' '},
			{' ', ' ', '|'},
			{' ', '-', ' '},
			{'|', ' ', ' '},
			{' ', '-', ' '}
		},
		{
			{' ', '-', ' '},
			{' ', ' ', '|'},
			{' ', '-', ' '},
			{' ', ' ', '|'},
			{' ', '-', ' '}
		},
		{
			{' ', ' ', ' '},
			{'|', ' ', '|'},
			{' ', '-', ' '},
			{' ', ' ', '|'},
			{' ', ' ', ' '}
		},
		{
			{' ', '-', ' '},
			{'|', ' ', ' '},
			{' ', '-', ' '},
			{' ', ' ', '|'},
			{' ', '-', ' '}
		},
		{
			{' ', '-', ' '},
			{'|', ' ', ' '},
			{' ', '-', ' '},
			{'|', ' ', '|'},
			{' ', '-', ' '}
		},
		{
			{' ', '-', ' '},
			{' ', ' ', '|'},
			{' ', ' ', ' '},
			{' ', ' ', '|'},
			{' ', ' ', ' '}
		},
		{
			{' ', '-', ' '},
			{'|', ' ', '|'},
			{' ', '-', ' '},
			{'|', ' ', '|'},
			{' ', '-', ' '}
		},
		{
			{' ', '-', ' '},
			{'|', ' ', '|'},
			{' ', '-', ' '},
			{' ', ' ', '|'},
			{' ', '-', ' '}
		}
	};
};

template <typename ... args>
MultiDigit<args...>::operator const char*() const
{
	return this->string;
}

template <typename ... Args>
constexpr MultiDigit<Args...>::MultiDigit(Args ... args) : string{}, digits{args...}
{
	unsigned int next = 0;

	for (unsigned int row = 0; row < 5; ++row)
	{
		for (unsigned int num = 0; num < sizeof...(Args); ++num)
		{
			for (unsigned int i = 0; i < 3; ++i)
			{
				string[next++] = numbers[digits[num]][row][i];
			}
			string[next++] = ' ';
		}
		string[next - 1] = '\n';
	}
	string[next] = '\0';
}


#endif
