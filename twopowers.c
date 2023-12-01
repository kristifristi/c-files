#include <stdio.h>
#include <unistd.h>

void main()
{
	unsigned long long int a = 1;
	int i = 0;
	while(1)
	{
		printf("2 to power %d: %llu\n", i, a);
		a <<= 1;
		++i;
		usleep(500000);
	}
	return;
}


