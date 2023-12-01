#include <stdio.h>

void printIntArray(int array[], int elems)
{
	for (int i = 0; i < elems - 1; ++i)
	{
		printf("%d, ", array[i]);
	}
	printf("%d", array[elems - 1]);
}


int main()
{
	int bar = 4;
	int foo [bar][bar];
	printf("foo[%d] full size: %li, foo list number: %li\n",  bar, sizeof(foo), (sizeof(foo) / sizeof(int)));
	for (int i = 0; i < bar*bar; ++i)
	{
		foo[i/bar][i%bar] = i;
		printf("%d, ", foo[i/bar][i%bar]);
	}
	int intArrayElems = sizeof(foo) / sizeof(foo[0]);
	printf("\n[");
	printIntArray(foo[2], intArrayElems);
	printf("]\n");
	for (int i = 0; i < bar; ++i)
	{
		printIntArray(foo[i], bar);
		printf("\n");
	}

}
