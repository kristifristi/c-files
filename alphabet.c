#include <stdio.h>

int main()
{
	int startLowerCase = 97;
	int startUpperCase = 65;
	int i;
	for(i = 0; i < 26; ++i)
	{
		printf("%c%c\n", startLowerCase + i, startUpperCase + i);
	}
	return 0;
}

