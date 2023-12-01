#include <stdio.h>
int main()
{
	
	float fahrenheit;
	float celsius;
	
	printf("Enter Fahrenheit: ");
	scanf("%f", &fahrenheit);
	
	celsius = (fahrenheit -32) * 5.0 / 9.0;
	printf("Celsius: %f\n", celsius);
	return 0;
}
