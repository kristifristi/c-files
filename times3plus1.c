#include <stdio.h>
#include <unistd.h>

void main() 
{
	unsigned int invoer;
	printf("geef integer\n");
	scanf("%u",&invoer);
	do
	{
		usleep(500000);
		printf("%u\n", invoer);
		if (invoer % 2 == 0)
		{
			invoer = invoer / 2;
		}
		else
		{
			invoer = invoer * 3 + 1;
		}
	}
	while (invoer != 1);
}
