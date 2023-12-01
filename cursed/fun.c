#include <stdio.h>
#include <string.h>

int funa(int x)
{
	return x+x;
}

int funb(int x)
{
	return x*10;
}


int main()
{
	int (*fp)(int) = funa;

	printf("result of fp(4): %d\t", fp(4));
	printf("altering...\n");
	fp = funb;
	printf("result of fp(4): %d\n", fp(4));
	return 0;
}

//returntype (*identifier)(param type(s))
