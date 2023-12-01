#include <stdio.h>
#include "octpatterns-raylib.h"

int main() {
	const int screenWidth = 1000;
   	const int screenHeight = 1000;
	const Color orange = { 252, 136, 5, 255 };
	InitWindow(screenWidth, screenHeight, "pattern output");
	SetTargetFPS(60);

	char pattern[255];
	char buf[255];
	int dir = 0;
	while(!WindowShouldClose()) { 
		printf("pattern angles: ");
		fgets(buf, 255, stdin);
		int patternLen = stringToPatternAngles(buf, pattern, 255);
		printf("starting angle: ");
		fgets(buf, 255, stdin);
		sscanf( buf, "%d", &dir);
		dir %= 8;
		printf("pattern value: 0x%lx\n\n", parsePattern(pattern, patternLen));
		BeginDrawing();
			ClearBackground(BLACK);
		EndDrawing();
		DrawPatternDoubleInd(dir, pattern, patternLen, 500, 500, 40, orange);
	
	}
	CloseWindow();
	return 0;
}

