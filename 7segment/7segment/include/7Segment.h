#ifndef SEGMENT_H
#define SEGMENT_H

template <class... _Ty>
class MultiDigit
{
public:

	operator const char*() const
	{
		return this->string;
	}


	_NODISCARD _CONSTEXPR17 explicit MultiDigit(_Ty ... rest) : string{}, digits{rest...}
	{
		unsigned int next = 0;
		for (unsigned int row = 0; row < 5; ++row)
		{
			for (unsigned int num = 0; num < sizeof...(_Ty); ++num)
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


private:
	char string[sizeof...(_Ty) * 20 + 1];
	int digits[sizeof...(_Ty)];

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

#endif // SEGMENT_H
