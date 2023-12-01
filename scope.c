#include <stdio.h>

void scope()
{
	printf(somewhere);
	return;
}

int main()
{
	char somewhere[6] = "here!";
	scope();
	return 0;
}
