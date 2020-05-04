#include "../include/OptParser.h"
#include <cstring>

bool CmdLineOptParser::Parse(int argc, char* argv[])
{

	bool valid = false;
	bool argSpace = false;

	char lastChar = false;

	for (int i = 1; i < argc; i++)
	{
		size_t argLen = strlen(argv[i]);
		if (argLen < 2) return false; // to short
		
		if (argv[i][0] == '-') // argument detected
		{
			if (argSpace)
			{
				valid = Option(lastChar, nullptr);
				if (!valid) return false;

				argSpace = false;
			}
			if (argLen == 2) // bool or space arg
			{
				argSpace = true;
				lastChar = argv[i][1];
			} else
			{
				if (argLen < 3) return false;
				if (argv[i][2] == '=') //-x=value
				{
					valid = Option(argv[i][1], &argv[i][3]);
					if (!valid) return false;
				} else
				{
					valid = Option(argv[i][1], &argv[i][2]);
					if (!valid) return  false;
				}
			}
		} else
		{
			if (argSpace)
			{
				if (!lastChar) return false; // Error in parsing, should not happen
				valid = Option(lastChar, &argv[i][0]);
				if (!valid) return false;
				argSpace = false;
			} else
			{
				return false;
			}
		}
	}
	return valid;
}

bool CmdLineOptParser::Option(const char c, const char* info)
{
	if (c != '\0') {
		if (info == nullptr) {
			return true;
		}

		// check if info contains only valid characters
		size_t i = 0;
		size_t infoLen = strlen(info);
		while (info[i] != '\0' && i < infoLen) {

			//  representable characters are from 32-126 (including)
			if (info[i] < 32 || info[i] > 126) {
				return false;
			}
			i++;
		}

		return true;
	}
	return false;
}
