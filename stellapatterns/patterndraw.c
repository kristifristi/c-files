#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
unsigned long makeX11Color(int r, int g, int b);
void drawPattern(Display* display, Drawable d, GC gc, int startAngle, char* angles, int length, short startx, short starty, int size);
long unsigned parsePattern(char* patternAngles, unsigned length);
int stringToPatternAngles(char*	string, char* patternAngles, int maxPatternLength);
int main() {
	unsigned long background, border;
	int screen_num; 
	int width, height;
	Window win; 
	XEvent ev;
	Display *dpy;
	GC gc; 
	dpy = XOpenDisplay(NULL);

	screen_num = DefaultScreen(dpy);
	background = BlackPixel(dpy, screen_num);
	border = WhitePixel(dpy, screen_num);

	width = 512;
	height = 512;

	win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 
		width, height, 2, border, background);
	gc = XCreateGC(dpy, win, 0, 0);
	XMapWindow(dpy, win);
	XSetForeground(dpy, gc, makeX11Color(252, 136, 5));
	XDrawPoint(dpy, win, gc, 10, 10);
	char pattern[255];
	char buf[255];
	//char pattern[] = { 2, 7, 0, 3, 6, 3, 0, 6, 2, 0, 2, 7, 2, 2, 6 };
	//char pattern[] = { 0, 0, 0, 3, 2, 6, 2 };
	//char pattern[] = { 0, 3, 0, 5, 0, 5, 0 };
	//char pattern[] = { 0, 2, 1};
	int dir = 0;
	while(1) { 
		XClearWindow(dpy, win);
		printf("pattern angles: ");
		fgets(buf, 255, stdin);
		int patternLen = stringToPatternAngles(buf, pattern, 255);
		printf("starting angle: ");
		fgets(buf, 255, stdin);
		sscanf( buf, "%d", &dir);
		dir %= 8;
		printf("pattern value: 0x%lx\n\n", parsePattern(pattern, patternLen));
		drawPattern(dpy, win, gc, dir, pattern, patternLen, 256, 256, 20);
		//dir = (dir + 2) % 8;
	}
	return 0;
}


unsigned long makeX11Color(int r, int g, int b)
{
	return b + (g<<8) + (r<<16);
}

void drawPattern(Display* display, Drawable d, GC gc, int startAngle, char* patternAngles, int length, short startx, short starty, int size)
{
	int prevx = startx;
	int prevy = starty;
	int currentdir = startAngle;
	short dirs[8][2] = {
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },
		{ -1, 1 },
		{ -1, 0 },
		{ -1, -1 },
		{ 0, -1 },
		{ 1, -1 }
	};
	XDrawArc(display, d, gc, startx, starty, 5, 5, 0, 360 * 64);
	XPoint* points = malloc((length + 2) * sizeof(XPoint));
	points[0].x = startx;
	points[0].y = starty;
	prevx += dirs[currentdir][0] * size;
	prevy += dirs[currentdir][1] * size;
	points[1].x = prevx;
	points[1].y = prevy;
	
	for (int i = 0; i < length; i++)
	{
		//char text[255];
		//sprintf(text, "%d", i);
		//XDrawString(display, d, gc, prevx, prevy, text, strlen(text));
		currentdir = ((currentdir + patternAngles[i]) % 8);
		prevx += dirs[currentdir][0] * size;
		prevy += dirs[currentdir][1] * size;
		points[i+2].x = prevx;
		points[i+2].y = prevy;
	}
	XDrawLines(display, d, gc, points, length + 2, CoordModeOrigin);
	free(points);
	XFlush(display);
	return;
}

long unsigned parsePattern(char* patternAngles, unsigned length)
{
	if(length > 31) return 0;
	long unsigned sum = 0;
	for(int i = 0; i < length; i++)
	{
		long unsigned temp = 4 - abs(patternAngles[i] - 4);
		sum += temp << (i*2);
	}
	return sum;
}

int stringToPatternAngles(char*	string, char* patternAngles, int maxPatternLength)
{
	for (int i = 0; i < maxPatternLength; i++)
	{
		int angle;
		switch(string[i])
		{
		case '0':
			angle = 0;
			break;
		case '1':
			angle = 1;
			break;
		case '2':
			angle = 2;
			break;
		case '3':
			angle = 3;
			break;
		case '4':
			angle = 4;
			break;
		case '5':
			angle = 5;
			break;
		case '6':
			angle = 6;
			break;
		case '7':
			angle = 7;
			break;
		default:
			return i;
		}
		patternAngles[i] = angle;
	}
	return maxPatternLength;
}
		
			
	
	
	
	
	
