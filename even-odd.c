#include <stdio.h>

int isOdd(int number)
{
	return number % 2;
}

int main()
{
	int input;
	char answer[2][5] = {"even", "odd"};
	printf("Integer please\n");
	scanf("%d", &input);
	printf("That's %s\n", answer[1 & input]);
	return 0;
}
