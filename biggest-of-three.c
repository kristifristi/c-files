#include <stdio.h>

int biggestThree( int a, int b, int c)
{
	int value;
	if (a > b)
	{
		value = a;
	}
	else
	{
		value = b;
	}
	
	if (value < c)
	{
		value = c;
	}
	return value;
}

int main()
{
	int first, second, third;
	printf("tell me about three integers\n");
	scanf("%d", &first);
	scanf("%d", &second);
	scanf("%d", &third);
	int biggest = biggestThree(first, second, third);
	printf("the biggest one is %d\n", biggest);
	return 0;
}
