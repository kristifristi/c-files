#include <stdio.h>
#include <stdlib.h>

void main()
{
	char *nasty = NULL;
	
	nasty = (char *) malloc(70000);
	printf("malloc gave me %u\n", nasty);
	return;
}
