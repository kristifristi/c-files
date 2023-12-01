#include <stdbool.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <unistd.h>
long unsigned parsePattern(char* patternAngles, unsigned length)// takes a list of pattern angles and uses my rules to turn it into a number
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

int stringToPatternAngles(char*	string, char* patternAngles, int maxPatternLength) //takes a string of numbers 0-7 (inclusive) and makes it into a list (of patternangles). halts if it encounters an invalid character. returns the langth of pattern it made
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

void XDrawPatternSimple(Display* display, Drawable d, GC gc, int startAngle, char* patternAngles, int length, short startx, short starty, int size)
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
	XPoint* points = malloc((length + 2) * sizeof(XPoint));
	points[0].x = startx;
	points[0].y = starty;
	prevx += dirs[currentdir][0] * size;
	prevy += dirs[currentdir][1] * size;
	points[1].x = prevx;
	points[1].y = prevy;
	
	for (int i = 0; i < length; i++)
	{
		currentdir = ((currentdir + patternAngles[i]) % 8);
		prevx += dirs[currentdir][0] * size;
		prevy += dirs[currentdir][1] * size;
		points[i+2].x = prevx;
		points[i+2].y = prevy;
	}
	int err = XDrawLines(display, d, gc, points, length + 2, CoordModeOrigin);
	printf("\n%d\n", err);
	free(points);
	XFlush(display);
	return;
}

void XDrawPatternUnambiguous(Display* display, Drawable d, GC gc, int angle, char* patternAngles, int length, short patternx, short patterny, int size)
{
	//XSelectInput(display, d, ExposureMask);
  	//XEvent ev;//apparently you need to wait for exposure events to draw the next line
	char buf[255];
	XDrawArc(display, d, gc, patternx-size/2, patterny-size/2, size/10, size/10, 0, 360 * 64); //gotta check what its origin is	
	angle %= 8; //fuck you
	short dirs[8][2] = {		//used to get the real positions of the points, and for truncating the lines drawn
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },
		{ -1, 1 },
		{ -1, 0 },
		{ -1, -1 },
		{ 0, -1 },
		{ 1, -1 }
	};
	short indicators[8][4][2] = {	//[dir][visits][x, y], scaled up tenfold
		{	{0, 0},		//1, 0
			{1, -1},
			{2, -1},
			{3, -1} },
		{	{0, 0},		//1, 1
			{2, 1},
			{3, 1},
			{3, 2},	},
		{	{0, 0},		//0, 1
			{1, 1},
			{1, 2},
			{1, 3}	},
		{	{0, 0},		//-1, 1
			{-1, 2},
			{-1, 3},
			{-2, 3} },
		{	{0, 0},		//-1, 0
			{-1, 1},
			{-2, 1},
			{-3, 1} },
		{	{0, 0},		//-1, -1
			{-2, -1},
			{-3, -1},
			{-3, 1} },	
		{	{0, 0},		//0, -1
			{-1, -1},
			{-1, -2},
			{-1, -3} },
		{	{0, 0},		//1, -1
			{1, -2},
			{1, -3},
			{2, -3}	}
	};	
	XPoint lines[3];	//used to draw the current lines and indicators
	XPoint enterInd[2];
	int visits = 0;
	int exitAngle = angle;
	int enterAngle = angle;
	XPoint* points = malloc((length + 2) * sizeof(XPoint));
	int* timesVisited = calloc(length + 2,sizeof(int)); //I want to assume thes are all zero
	points[0].x = patternx;
	points[0].y = patterny;
	timesVisited[0] = 1;
	//draw the first line with it's exit indicator
	lines[0].x = ((indicators[angle][visits][0] * size) / 10) + patternx;
	lines[0].y = ((indicators[angle][visits][1] * size) / 10) + patterny;
	lines[1].x = ((dirs[angle][0] * size) / 5) + patternx;	//the main line starts at 1/5 the distance
	lines[1].y = ((dirs[angle][1] * size) / 5) + patterny;
	lines[2].x = ((dirs[angle][0] * size * 4) / 5) + patternx;	//and ends at 4/5
	lines[2].y = ((dirs[angle][1] * size * 4) / 5) + patterny;
	int err = XDrawLines(display, d, gc, lines, 3, CoordModeOrigin);
	XGetErrorText(display, err, buf, 255);
	//XNextEvent(display, &ev);
	//get the second point
	patternx += dirs[angle][0] * size;
	patterny += dirs[angle][1] * size;
	points[1].x = patternx;
	points[1].y = patterny;
	timesVisited[1] = 1;
	int numOfPointsUsed = 2;
	
	//the main loop
	for(int n = 0; n < length; n++)
	{
		//draw the enter indicator of the line w
		enterInd[0].x = lines[2].x;	//pick up where we left off
		enterInd[0].y = lines[2].y;
		enterInd[1].x = ((indicators[(angle+4)%8][visits][0] * size) / 10) + patternx;//get the indicator for the opposite angle
		enterInd[1].y = ((indicators[(angle+4)%8][visits][1] * size) / 10) + patterny;
		XDrawLines(display, d, gc, enterInd, 2, CoordModeOrigin);//the indicator is just 2 points
		//process the next angle
		angle = (angle + patternAngles[n]) % 8;
		//draw our next line
		lines[0].x = ((indicators[angle][visits][0] * size) / 10) + patternx;
		lines[0].y = ((indicators[angle][visits][1] * size) / 10) + patterny;
		lines[1].x = ((dirs[angle][0] * size) / 5) + patternx;
		lines[1].y = ((dirs[angle][1] * size) / 5) + patterny;
		lines[2].x = ((dirs[angle][0] * size * 4) / 5) + patternx;
		lines[2].y = ((dirs[angle][1] * size * 4) / 5) + patterny;
		XDrawLines(display, d, gc, lines, 3, CoordModeOrigin);
		//move on to the next point
		patternx += dirs[angle][0] * size;
		patterny += dirs[angle][1] * size;
		bool foundPoint = false;
		for(int i = 0; i < numOfPointsUsed; i++)//finding out how many times a point has been used
		{
		if((patternx == points[i].x) && (patterny == points[i].y))
		{
			visits = ++timesVisited[i];
			foundPoint = true;
			break;
		}
		}
		if(!foundPoint)//what to do if the points has not yet been used
		{
		visits = 0;
		points[numOfPointsUsed].x = patternx;
		points[numOfPointsUsed].y = patterny;
		numOfPointsUsed++;
		}
	}
	//XNextEvent(display, &ev);
	free(points);
	free(timesVisited);
	return;
}





