#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swapValue(void* a, void *b, unsigned size)
{
	void *c = malloc(size);
	if (c == NULL) 
	{
		printf("malloc error\n");
		return -1;
	}
	memcpy(c, a, size);
	memcpy(a, b, size);
	memcpy(b, c, size);
	free(c);
	return 0;
}
/*
int main()
{
	int y = -1;
	int x = 413;
	printf("y: %d\tx: %d\n", y, x);
	swapValue(&y,&x, sizeof(y));
	printf("after swap:\ny: %d\tx: %d\n", y, x);
	return 0;
}
*/
