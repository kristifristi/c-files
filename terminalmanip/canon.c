#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main()
{
	struct termios settings;
	tcgetattr(1, &settings);
	settings.c_lflag &= ~ICANON;
	tcsetattr(1, TCSANOW, &settings);
	char input;
	printf("type something\n");
	while(1)
	{
		input = getchar();
		printf("\n0x%x\n", input);
	}
	return 0;
}
