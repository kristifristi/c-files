#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* test;
	int dpy;
	printf("looking for test.txt\n");
	test = fopen("test.txt", "r");
	if (test == NULL)
	{
		printf("test not found. making new file\n");
		test = fopen("test.txt", "w+");
		fprintf(test, "greetings.\nHow are you?\nFine, thank you.");
	}
	else
	{
		printf("test found. printing contents:\n");
		while(!feof(test))
		{
			dpy = fgetc(test);
			printf("%c", dpy);
		}
		printf("\nfile display complete\n");
	}
	fclose(test);
	return 0;
}

