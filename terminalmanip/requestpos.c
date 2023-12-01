#include <stdio.h>

void main()
{
	char response[8];
	printf("\033[6n\n");
	for(int i = 0; i < 8; i++)
	{
		response[i] = getchar();
	}
	printf("terminal response:\n");
	for(int i = 0; i < 8; i++)
	{
		printf("%x\t%c\n", response[i], response[i]);
	}
	return;
}
