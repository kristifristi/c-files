#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "octpatterns.h"
unsigned long makeX11Color(int r, int g, int b);
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
	int dir = 0;
	XSelectInput(dpy, win, ExposureMask);
	XNextEvent(dpy, &ev);
	while(1) { 
		XDrawPoint(dpy, win, gc, 20, 20);
		XClearWindow(dpy, win);
		printf("pattern angles: ");
		fgets(buf, 255, stdin);
		int patternLen = stringToPatternAngles(buf, pattern, 255);
		printf("starting angle: ");
		fgets(buf, 255, stdin);
		sscanf( buf, "%d", &dir);
		dir %= 8;
		printf("pattern value: 0x%lx\n\n", parsePattern(pattern, patternLen));
		XDrawPatternUnambiguous(dpy, win, gc, dir, pattern, patternLen, 256, 256, 20);
		//dir = (dir + 2) % 8;
	}
	return 0;
}


unsigned long makeX11Color(int r, int g, int b)
{
	return b + (g<<8) + (r<<16);
}
