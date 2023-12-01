#include <stdio.h>
#include <unistd.h>


void main()
{
	int state = 0;
	char c = '#';
	int loopIndex = 0;
	printf("\033[2J");
	while(1)
	{
		switch (state)
		{
		case 0:
			printf("\033[10;%df%c",11+ loopIndex, c);
			break;
		case 1:
			printf("\033[%d;20f%c",11 + loopIndex, c);
			break;
		case 2:
			printf("\033[20;%df%c",19 - loopIndex, c);
			break;
		case 3:
			printf("\033[%d;10f%c",19 - loopIndex, c);
			break;
		}
		fflush(stdout);	//makes printf actually print despite lack of newline
		if (loopIndex == 9)
		{
			state = (state + 1) % 4;
			loopIndex = 0;
			c = (state == 0) ? (c == '#') ? '@' : '#' : c;
		}
		else
		{
			++loopIndex;
		}
		usleep(200000);
	}
	return;
}
