#include <stdio.h>

int sign(float number)
{
	if(number == 0)
	{
		return 0;
	}
	else
	{
		if(number < 0)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}
}

int main()
{
	float inputNumber;
	char resultName[3][9] = {"negative", "zero", "positive"};
	printf("Give me a number.\n");
	scanf("%f", &inputNumber);
	printf("Your number is %s.\n", resultName[sign(inputNumber) + 1]);
}
