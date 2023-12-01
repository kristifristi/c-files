#include <stdio.h>
#include <unistd.h>

void main()
{
	char buf;
	printf("\033[2Jtype something\033[8m\033[?25l");
	buf = getchar();
	printf("\033[28mlol\n");
	printf("you typed:\n%c\n\033[?25h", buf);
	return;
}
