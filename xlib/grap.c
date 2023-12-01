#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

unsigned long makeX11Color(int r, int g, int b); //apparently x11 handles colors with long ints

int main() {
	unsigned long background, border;
	int screen_num; //numerical id of screen
	int width, height;	//dimensions of screen
	Window win; //window object
	XEvent ev;	//xlib event struct
	Display *dpy; //connection to display server
	GC gc; //I'm not really sure what a graphics context is, but you need it to draw things on the screen apparently
	Pixmap pxm;

	/*connection to display server*/
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
	for(int i = 0; i < 255; i++)
	{
		XSetForeground(dpy, gc, makeX11Color(0, i, i));
		for(int j = 0; j < 255; j++)
		{
			usleep(100);
			XDrawPoint(dpy, win, gc, i, j);
		}
	}
	sleep(1);
	XDrawPoint(dpy, win, gc, 50, 50);
	XSetForeground(dpy, gc, makeX11Color(0,50, 170));
	XFillRectangle(dpy, win, gc, 10, 10, 100, 100);
	XFlush(dpy);
	sleep(10);
	return 0;
}


unsigned long makeX11Color(int r, int g, int b)
{
	return b + (g<<8) + (r<<16);
}
