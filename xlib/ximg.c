#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 128

unsigned long makeX11Color(int r, int g, int b); //apparently x11 handles colors with long ints

int main() {
	printf("size: %d\n", SIZE);
	printf("clocks per sec? %lu\n", CLOCKS_PER_SEC);
	unsigned long background, border;
	int screen_num; //numerical id of screen
	int width, height;	//dimensions of screen
	Window win; //window object
	XEvent ev;	//xlib event struct
	Display *dpy; //connection to display server
	GC gc; //I'm not really sure what a graphics context is, but you need it to draw things on the screen apparently
	XImage *xim;
	char *ximdata = NULL;
	ximdata = (char *) malloc(SIZE * SIZE * 4 + 64);
	printf("data address: %u\n", ximdata);
	if(ximdata == NULL)
	{
		printf("malloc mean to me!\n");
		return -1;
	}
	/*connection to display server*/
	dpy = XOpenDisplay(NULL);

	screen_num = DefaultScreen(dpy);
	background = BlackPixel(dpy, screen_num);
	border = WhitePixel(dpy, screen_num);

	width = 512;
	height = 512;

	win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 
		width, height, 2, border, background);
	//XSelectInput(dpy, win, ButtonPressMask | KeyPressMask | PointerMotionMask);
	gc = XCreateGC(dpy, win, 0, 0);
	XMapWindow(dpy, win);
	XSetForeground(dpy, gc, makeX11Color(252, 136, 5));
	XDrawPoint(dpy, win, gc, 100, 100);
	
	xim = XCreateImage(dpy, XDefaultVisual(dpy, screen_num), 24, XYPixmap, 0, ximdata, SIZE, SIZE, 8, 0);
	XInitImage(xim);
	XFlush(dpy);
	int loopIndex = 0;
	time_t start;
	time_t end;
	float timeTaken;
	unsigned char *dumper = ximdata;
	sleep(1);
	while(1){
	loopIndex = (loopIndex + 1) % SIZE;
	start = clock();
	for(int i = 0; i < SIZE; i++)
	{
		//XSetForeground(dpy, gc, makeX11Color(i, 0, 0));
		for(int j = 0; j < SIZE; j++)
		{
			XPutPixel(xim, i, j, makeX11Color(i * (255/SIZE),0, 0));
		}
	}
	end = clock();
	XPutImage(dpy, win, gc, xim, 0, 0, 0, 0, SIZE, SIZE);
	
	printf("time taken: %ld\n", end - start);
	usleep(50000);
	break;
	}
	long last = 0;
	unsigned char currentVal = dumper[0];
	printf("starting value: %02x\n", currentVal);
	printf("index, change, spacing:");
	for(int i = 0; i < SIZE * SIZE * 4 + 64; i++)
	{
		if (dumper[i] != currentVal)
		{
			printf("%04x", i);
			printf(" %02x", dumper[i]);
			printf(" %04x\n", i - last);
			last = i;
			currentVal = dumper[i];
		}
			
	}
	printf("final uninterupted stretch: %04x\n", (SIZE * SIZE * 4 + 64) - last);
	printf("\n");

/*	while(1)
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
			printf("(%d, %d)\n", ev.xmotion.x, ev.xmotion.y);
		}
	}
*/	while(1) { }
	return 0;
}


unsigned long makeX11Color(int r, int g, int b)
{
	return b + (g<<8) + (r<<16);
}
