#include "../include/Printf.h"

int main(int argc, char* argv[])
{
	char dst[100];
	unsigned int x = -345;
	
	Printf(dst, &dst[99], "int: %d; unsigned int: %u; char: %c; string: %s; hex: %x; binary: %b; percent: %%",10, x, 'c', "TEST", 0x000AB, 0b0001);

	return 0;
}
