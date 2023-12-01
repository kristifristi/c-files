#include <stdio.h>
#include "style.h"
#include <unistd.h>

int main()
{
	struct RGB ourple = { 162, 17, 224 };
	setTxtColorRGB(ourple.r, ourple.g, ourple.b);
	setBGColorRGB(200, 180, 10);
	setTextStyle(BLINKING);
	printf("test\n\n");
	sleep(2);
	setTextStyle(RESET_STYLE);
	clrScreen();
	pushprint();
	return 0;
}
