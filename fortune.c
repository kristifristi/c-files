#include <stdio.h>

int main()
{
	int luck;
	char fortune[4][62] = {"You will meet someone important soon",
	"You already have everything you need to accomplish your goals",
	"a risk you've taken recently will not end well",
	"someone you disagreed with recently will turn out to be right"};
	
	printf("Pick a number from 1 to 4: ");
	scanf("%d", &luck);
	printf("Here is your fortune:\n%s\n", fortune[luck]);
}
