#include <stdio.h>

void main()
{
	int a = 0;
	unsigned int b = 0;
	int c;
	a = ~a;
	b = ~b;
	c = b >> 3;
	printf("bitwise not 0(two's complement): %d\n", b);
	printf("bitwise not 0(unsigned): %u\n", b);
	printf("-1 >> 1: %d\n", c);
	return;
}
