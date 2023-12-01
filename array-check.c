#include <stdio.h>

int vowelcheck(int input)
{
	int isInArrayBool = 0;
	int numbers[5] = { 6, 5, 4, 3, 2 };
	int index;
	for (index = 0; index < 5; ++index)
	{
		printf("%d\n", numbers[index]);
		if (input == numbers[index])
		{
			isInArrayBool = 1;
			break;
		}
	}
	printf("%d\n", isInArrayBool);
	return isInArrayBool;
}

int main()
{
	int number = 5;
	int result = vowelcheck(number);
	if (result)
	{
		printf("%d's in\n", number);
	}
	else
	{
		printf("%d's out\n", number);
	}
	return 0;
}
