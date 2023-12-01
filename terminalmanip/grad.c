#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int triwave(int x)
{
	return abs(128 - (x%255));
}

void main()
{
	int r = 0, g = 0, b = 0;
	long int i = 0;
	printf("\033[?25l\n");
	while(1)
	{
		printf("\033[48;2;%d;%d;%dm\033[2J\n", r, g, b);
		r = triwave(i*3);
		g = triwave(i*2);
		b = triwave(i);
		usleep(50000);
		++i;
	}
	return;
}
