#include <stdio.h>

const int one = 1;
const int two = 2;

void main()
{
	int* ptr = &one;
	printf("%d\n", *ptr);
	*ptr = 3;
	printf("%d\n", *ptr);
	return;
}

