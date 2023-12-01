#include <stdio.h>

int main()
{
	char operator;
	float first_number;
	float second_number;
	printf("choose operator(+, -, *, /):");
	scanf("%c", &operator);
	printf("choose first operand:");
	scanf("%f", &first_number);
	printf("choose second operand:");
	scanf("%f", &second_number);
	switch (operator)
	{
		case 43 :
			printf("%f + %f = %f\n", first_number, second_number, first_number + second_number);
			break;
		case 45 :
			printf("%f - %f = %f\n", first_number, second_number, first_number - second_number);
			break;
		case 42 :
			printf("%f * %f = %f\n", first_number, second_number, first_number * second_number);
			break;
		case 47 :
			printf("%f / %f = %f\n", first_number, second_number, first_number / second_number);
			break;
		default:
			printf("invalid operator\n");
	}
	return 0;
}
