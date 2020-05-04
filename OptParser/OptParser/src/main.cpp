#include "../include/OptParser.h"

int main(int argc, char* argv[])
{
	CmdLineOptParser parser;
	const bool result = parser.Parse(argc, argv);

	return 0;
}
