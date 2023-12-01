#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define IM_W 512
#define IM_H 128
#define WIN_SIZE 512

unsigned long makeX11Color(int r, int g, int b); //apparently x11 handles colors with long ints
unsigned long pixelRule(int x, int y);

int main() {
	Window win; 
	XEvent ev;
	Display *dpy;
	GC gc; 
	unsigned long background, border;
	int screen_num;
	XImage *xim;
	char *ximdata = NULL;
	ximdata = (char *) malloc(IM_H * IM_W * 4 + 64);
	if(ximdata == NULL)
	{
		printf("malloc mean to me!\n");
		return -1;
	}
	dpy = XOpenDisplay(NULL);

	screen_num = DefaultScreen(dpy);
	background = BlackPixel(dpy, screen_num);
	border = WhitePixel(dpy, screen_num);


	win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 
		WIN_SIZE, WIN_SIZE , 2, border, background);
	gc = XCreateGC(dpy, win, 0, 0);
	XMapWindow(dpy, win);
	xim = XCreateImage(dpy, XDefaultVisual(dpy, screen_num), 24, XYPixmap, 0, ximdata, IM_W, IM_H, 8, 0);
	XInitImage(xim);
	XFlush(dpy);
	int realX;
	time_t start = clock();
	for(int i = 0; i < WIN_SIZE/IM_H; i++)
	{
		for(int j = 0; j < IM_H; j++)
		{
			int realY = j + i * IM_H;
			for(int k = 0; k < IM_W; k++)
			{
				XPutPixel(xim, k, j, pixelRule(k, realY));
				//printf("put %lx at %d, %d\n", pixelRule(k, realY), k, realY);
			}
		}
		XPutImage(dpy, win, gc, xim, 0, 0, 0, i * IM_H, IM_W, IM_H);
	}
	printf("time taken: %lu\n", clock() - start);
	while(1) { }
	return 0;
}


unsigned long makeX11Color(int r, int g, int b)
{
	return b + (g<<8) + (r<<16);
}

unsigned long pixelRule(int x, int y)
{
	return makeX11Color(x / 2, y / 2 , 0);
}
