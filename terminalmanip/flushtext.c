#include <stdio.h>
#include <unistd.h>

void main()
{
	printf("1 ");
	fflush(stdout);
	sleep(1);
	printf("2 ");
	fflush(stdout);
	sleep(1);
	printf("3\n");
	return;
}
