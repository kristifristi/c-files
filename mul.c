#include <stdio.h>

int main()
{
	//declare
	float firstInput;
	float secondInput;

	//ask for inputs
	printf("Enter A: ");
	scanf("%f", &firstInput);
	printf("Enter B: ");
	scanf("%f", &secondInput);

	//give result
	printf("A x B = %f", firstInput * secondInput);

	return 0;
}
