#include <stdio.h>
#include <unistd.h>

void main()
{
	printf("\033[10;10Hwow\n");
	sleep(1);
	printf("\033[9Cnice\n");
	return;
}
