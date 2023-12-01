#include <time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define IM_W 512
#define IM_H 64
#define WIN_SIZE 512
float findDistance(float ax, float ay, float bx, float by);
unsigned long makeX11Color(int r, int g, int b); //apparently x11 handles colors with long ints
float triWave(float t);
unsigned long pixelRule(int x, int y, int step);
int waveVal(float px, float py, float ox, float oy, float step, float len, float amp);

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
	int index = 0;
	while(1){
	time_t start = clock();
	for(int i = 0; i < WIN_SIZE/IM_H; i++)
	{
		for(int j = 0; j < IM_H; j++)
		{
			int realY = j + i * IM_H;
			for(int k = 0; k < IM_W; k++)
			{
				XPutPixel(xim, k, j, pixelRule(k, realY, index));
				//printf("put %lx at %d, %d\n", pixelRule(k, realY), k, realY);
			}
		}
		XPutImage(dpy, win, gc, xim, 0, 0, 0, i * IM_H, IM_W, IM_H);
		XFlush(dpy);
	}
	printf("time taken: %lu\n", clock() - start);
	index++;
	float findex = index;
	printf("triwave: %f\n\n", triWave(findex/100)*400);
	//break;
	}
	while(1) { }
	return 0;
}


unsigned long makeX11Color(int r, int g, int b)
{
	return b + (g<<8) + (r<<16);
}
int waveVal(float px, float py, float ox, float oy, float step, float len, float amp)
{
	float distance = findDistance(px, py, ox, oy);
	float wave = cos((distance + step)/len);
	return wave * amp;
}

float triWave(float t)
{
	return fabsf(fmodf(t, 2) - 1) - 1;
}

float findDistance(float ax, float ay, float bx, float by)
{
	ax -= bx;
	ay -= by;
	return sqrt(ax*ax + ay*ay);
}
unsigned long pixelRule(int x, int y, int step)
{
	int value = 128;
	float fx = x;
	float fy = y;
	float fs = step;
	//value = 255 / (findDistance(x, y, x, triWave(fx/50) * 50+ 255)/ 10);
	//value = (value > 255) ? 255 : value;
	float tfs = (triWave(fs/400) + 1) * 400;
	value += waveVal(x, y, 255, 255, 0, 5, 64);
	value += waveVal(x, y, 50 + tfs, 50 + tfs, 0, 5, 64);
	return makeX11Color(value, value, value);
}
