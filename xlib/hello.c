#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long makeX11Color(int r, int g, int b); //apparently x11 handles colors with long ints

int main() {
	unsigned long background, border;
	int screen_num; //numerical id of screen
	int width, height;	//dimensions of screen
	Window win; //window object
	XEvent ev;	//xlib event struct
	Display *dpy; //connection to display server
	GC gc; //I'm not really sure what a graphics context is, but you need it to draw things on the screen apparently


	/*connection to display server*/
	dpy = XOpenDisplay(NULL);
	//handle error?

	screen_num = DefaultScreen(dpy);
	background = BlackPixel(dpy, screen_num);
	border = WhitePixel(dpy, screen_num);

	width = 100;
	height = 100;

	win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 
		width, height, 2, border, background);
	XSelectInput(dpy, win, ButtonPressMask | KeyPressMask | PointerMotionMask);
	gc = XCreateGC(dpy, win, 0, 0);
	XMapWindow(dpy, win);
	XSetForeground(dpy, gc, makeX11Color(252, 136, 5));
	while(1)
	{
		XNextEvent(dpy, &ev);
		switch(ev.type){
//		case ButtonPress:
//			XDrawPoint(dpy, win, gc, ev.xbutton.x, ev.xbutton.y);
			break;
		case KeyPress:
			printf("%u\n", ev.xkey.keycode);
			break;
		case MotionNotify:
			XDrawPoint(dpy, win, gc, ev.xmotion.x, ev.xmotion.y);
		}
		printf("%lu\n", clock());
	}
	return 0;
}


unsigned long makeX11Color(int r, int g, int b)
{
	return b + (g<<8) + (r<<16);
}
