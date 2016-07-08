#include <stdio.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	unsigned char		*pchar;
	unsigned int		*pint;

	pchar = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	pint = (unsigned int*)pchar;
	pchar[0] = 0x12;
	pchar[1] = 0x34;
	pchar[2] = 0x56;
	pchar[3] = 0x78;
	printf("%X", *pint);

	return (0);
}