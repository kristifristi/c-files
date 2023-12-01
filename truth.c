#include <stdio.h>
int xor[2][2] = {1, 1, 0, 1};

void main()
{
	int a;
	int b;
	while(1)
	{
		printf("input a and b\n");
		scanf("%d %d", &a, &b);
		printf("output value a -> b: %d\n\n", xor[a][b]);
	}
}

