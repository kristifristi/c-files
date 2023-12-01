#include <stdio.h>

int main()
{
	//declare
	int left;
	int right;
	int leftmemory;
	
	//ask for input
	printf("what are your two numbers?\n");
	scanf("%d%d", &left, &right);
	
	//swap
	leftmemory = left;
	left = right;
	right = leftmemory;
	
	//tell
	printf("you mean %d and %d? >:)", left, right);
	
	return 0;
}

