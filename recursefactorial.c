#include <stdio.h>

unsigned int factorial(unsigned int num)
{
	
	if (num == 1)
	{
		return num;
	}
	else
	{
	 	return num * factorial(num - 1);
	}
}

int main()
{
	int inputNumber;
	printf("what do you want the factorial of? ");
	scanf("%d", &inputNumber);
	printf("the factorial of %d is %d\n", inputNumber, factorial(inputNumber));
	return 0;
}
