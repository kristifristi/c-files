#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
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

void DrawPatternSimple(int startAngle, char* patternAngles, int length, short startx, short starty, int size, Color color) //for when you want to be secretive/minimalist
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
	Vector2* points = malloc((length + 2) * sizeof(Vector2));
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
	DrawLineStrip(points, length + 2, color);
	free(points);
	return;
}

void DrawPatternUnambiguous(int angle, char* patternAngles, int length, short patternx, short patterny, int size, Color color)	//not sure why I want to keep this around...
{
	char buf[255];
	BeginDrawing();
	DrawCircleLines(patternx, patterny, size*2/10, color); //gotta check what its origin is	
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
			{1, -2},
			{3, -2},
			{5, -2} },
		{	{0, 0},		//1, 1
			{3, 1},
			{5, 1},
			{5, 3},	},
		{	{0, 0},		//0, 1
			{2, 1},
			{2, 3},
			{2, 5}	},
		{	{0, 0},		//-1, 1
			{-1, 3},
			{-1, 5},
			{-3, 5} },
		{	{0, 0},		//-1, 0
			{-1, 2}, 
			{-3, 2},
			{-5, 2} },
		{	{0, 0},		//-1, -1
			{-3, -1},
			{-5, -1},
			{-5, -3} },	
		{	{0, 0},		//0, -1
			{-2, -1},
			{-2, -3},
			{-2, -5} },
		{	{0, 0},		//1, -1
			{1, -3},
			{1, -5},
			{3, -5}	}
	};	
	Vector2 lines[3];	//used to draw the current lines and indicators
	Vector2 enterInd[2];
	int visits = 0;
	int exitAngle = angle;
	int enterAngle = angle;
	Vector2* points = malloc((length + 2) * sizeof(Vector2));
	int* timesVisited = calloc(length + 2,sizeof(int)); //I want to assume thes are all zero
	points[0].x = patternx;
	points[0].y = patterny;
	//draw the first line with it's exit indicator
	lines[0].x = ((indicators[angle][visits][0] * size) / 10) + patternx;
	lines[0].y = ((indicators[angle][visits][1] * size) / 10) + patterny;
	lines[1].x = ((dirs[angle][0] * size * 3) / 10) + patternx;	//the main line starts at 3/10 the distance
	lines[1].y = ((dirs[angle][1] * size * 3) / 10) + patterny;
	lines[2].x = ((dirs[angle][0] * size * 7) / 10) + patternx;	//and ends at 7/10
	lines[2].y = ((dirs[angle][1] * size * 7) / 10) + patterny;
	DrawLineStrip(lines, 3, color);
	EndDrawing();
	patternx += dirs[angle][0] * size;
	patterny += dirs[angle][1] * size;
	points[1].x = patternx;
	points[1].y = patterny;
	int numOfPointsUsed = 2;
	
	//the main loop
	for(int n = 0; n < length; n++)
	{
		BeginDrawing();
		DrawCircle(patternx, patterny, size/20, color);
		//draw the enter indicator of the previous line
		enterInd[0].x = lines[2].x;	//pick up where we left off
		enterInd[0].y = lines[2].y;
		enterInd[1].x = ((indicators[(angle+4)%8][visits][0] * size) / 10) + patternx;//get the indicator for the opposite angle
		enterInd[1].y = ((indicators[(angle+4)%8][visits][1] * size) / 10) + patterny;
		DrawLineStrip(enterInd, 2, color);//the indicator is just 2 points
		//process the next angle
		angle = (angle + patternAngles[n]) % 8;
		//draw our next line
		lines[0].x = ((indicators[angle][visits][0] * size) / 10) + patternx;
		lines[0].y = ((indicators[angle][visits][1] * size) / 10) + patterny;
		lines[1].x = ((dirs[angle][0] * size * 3) / 10) + patternx;
		lines[1].y = ((dirs[angle][1] * size * 3) / 10) + patterny;
		lines[2].x = ((dirs[angle][0] * size * 7) / 10) + patternx;
		lines[2].y = ((dirs[angle][1] * size * 7) / 10) + patterny;
		DrawLineStrip(lines, 3, color);
		EndDrawing();
		//move on to the next point
		patternx += dirs[angle][0] * size;
		patterny += dirs[angle][1] * size;
		bool foundPoint = false;
		for(int i = 0; i < numOfPointsUsed; i++)//finding out how many times a point has been used
		{
		if((patternx == points[i].x) && (patterny == points[i].y))
		{
			visits = (++timesVisited[i] < 4) ? timesVisited[i] : 0;
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
	free(points);
	free(timesVisited);
	return;
}

void DrawPatternDoubleInd(int angle, char* patternAngles, int length, short patternx, short patterny, int size, Color color)//hopefully this looks nice
{
	char buf[255];
	BeginDrawing();
	DrawCircleLines(patternx, patterny, size/3, color); //gotta check what its origin is	
	angle %= 8; //fuck you
	const short dirs[8][2] = {		//used to get the real positions of the points, and for truncating the lines drawn
		{ 1, 0 },
		{ 1, 1 },
		{ 0, 1 },
		{ -1, 1 },
		{ -1, 0 },
		{ -1, -1 },
		{ 0, -1 },
		{ 1, -1 }
	};
	const short indicators[8][4][2][2] = {	//[dir][visits][part1, part2][x, y], scaled up tenfold 
		{	{{ 0, 0}, { 2, 0}},	//1, 0
			{{ 1,-1}, { 1, 1}},
			{{ 2,-1}, { 2, 1}},
			{{ 3,-1}, { 3, 1}}	},
		{	{{ 0, 0}, { 2, 2}},	//1, 1
			{{ 2, 1}, { 1, 2}},
			{{ 3, 1}, { 1, 3}},
			{{ 3, 2}, { 2, 3}}	},
		{	{{ 0, 0}, { 0, 2}},	//0, 1
			{{ 1, 1}, {-1, 1}},
			{{ 1, 2}, {-1, 2}},
			{{ 1, 3}, {-1, 3}}	},
		{	{{ 0, 0}, {-2, 2}},	//-1, 1
			{{-1, 2}, {-2, 1}},
			{{-1, 3}, {-3, 1}},
			{{-2, 3}, {-3, 2}}	},
		{	{{ 0, 0}, {-2, 0}},	//-1, 0
			{{-1, 1}, {-1,-1}},
			{{-2, 1}, {-2,-1}},
			{{-3, 1}, {-3,-1}}	},
		{	{{ 0, 0}, {-2,-2}},	//-1, -1
			{{-2,-1}, {-1,-2}},
			{{-3,-1}, {-1,-3}},
			{{-3,-2}, {-2,-3}}	},	
		{	{{ 0, 0}, { 0,-2}},	//0, -1
			{{-1,-1}, { 1,-1}},
			{{-1,-2}, { 1,-2}},
			{{-1,-3}, { 1,-3}}	},
		{	{{ 0, 0}, { 2,-2}},	//1, -1
			{{ 1,-2}, { 2,-1}},
			{{ 1,-3}, { 3,-1}},
			{{ 2,-3}, { 3,-2}}	}
	};	//dear depths below If only i tried to make these progammatically (do that btw)
	Vector2 lines[2];	//used to draw the current lines
	Vector2 ind[3];		//used for the indicators
	int visits = 0;
	int exitAngle = angle;
	int enterAngle = angle;
	Vector2* points = malloc((length + 2) * sizeof(Vector2));
	int* timesVisited = calloc(length + 2,sizeof(int)); //I want to assume thes are all zero
	points[0].x = patternx;
	points[0].y = patterny;
	//draw the first line
	lines[0].x = ((dirs[angle][0] * size * 2) / 10) + patternx;	//the main line starts at 2/10 the distance
	lines[0].y = ((dirs[angle][1] * size * 2) / 10) + patterny;
	lines[1].x = ((dirs[angle][0] * size * 8) / 10) + patternx;	//and ends at 2/10
	lines[1].y = ((dirs[angle][1] * size * 8) / 10) + patterny;
	DrawLineStrip(lines, 2, color);
	ind[0].x = ((indicators[angle][visits][0][0] * size) / 10) + patternx;	//first part of indicator
	ind[0].y = ((indicators[angle][visits][0][1] * size) / 10) + patterny;
	ind[1].x = lines[0].x;				//attachment to main line
	ind[1].y = lines[0].y;
	ind[2].x = ((indicators[angle][visits][1][0] * size) / 10) + patternx;	//second part of indicator
	ind[2].y = ((indicators[angle][visits][1][1] * size) / 10) + patterny;
	DrawLineStrip(ind, 3, color);
	EndDrawing();
	patternx += dirs[angle][0] * size;
	patterny += dirs[angle][1] * size;
	points[1].x = patternx;
	points[1].y = patterny;
	int numOfPointsUsed = 2;			//register the first two points
	
	//the main loop
	for(int n = 0; n < length; n++)
	{
		BeginDrawing();
		DrawCircle(patternx, patterny, size/40, color);
		//draw the enter indicator of the previous line
		ind[1].x = lines[1].x;	//pick up where we left off
		ind[1].y = lines[1].y;
		int oppositeAngle = (angle+4)%8; //we need the indicator for the opposite angle
		ind[0].x = ((indicators[oppositeAngle][visits][0][0] * size) / 10) + patternx;
		ind[0].y = ((indicators[oppositeAngle][visits][0][1] * size) / 10) + patterny;
		ind[2].x = ((indicators[oppositeAngle][visits][1][0] * size) / 10) + patternx;
		ind[2].y = ((indicators[oppositeAngle][visits][1][1] * size) / 10) + patterny;
		DrawLineStrip(ind, 3, color);
		//process the next angle
		angle = (angle + patternAngles[n]) % 8;
		//draw our next line
		lines[0].x = ((dirs[angle][0] * size * 2) / 10) + patternx;
		lines[0].y = ((dirs[angle][1] * size * 2) / 10) + patterny;
		lines[1].x = ((dirs[angle][0] * size * 8) / 10) + patternx;
		lines[1].y = ((dirs[angle][1] * size * 8) / 10) + patterny;
		DrawLineStrip(lines, 2, color);
		//draw its exit ind
		ind[0].x = ((indicators[angle][visits][0][0] * size) / 10) + patternx;
		ind[0].y = ((indicators[angle][visits][0][1] * size) / 10) + patterny;
		ind[1].x = lines[0].x;
		ind[1].y = lines[0].y;
		ind[2].x = ((indicators[angle][visits][1][0] * size) / 10) + patternx;
		ind[2].y = ((indicators[angle][visits][1][1] * size) / 10) + patterny;
		DrawLineStrip(ind, 3, color);
		EndDrawing();
		//move on to the next point
		patternx += dirs[angle][0] * size;
		patterny += dirs[angle][1] * size;
		bool foundPoint = false;
		for(int i = 0; i < numOfPointsUsed; i++)//finding out how many times a point has been used
		{
		if((patternx == points[i].x) && (patterny == points[i].y))
		{
			visits = (++timesVisited[i] < 4) ? timesVisited[i] : 0;
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
	free(points);
	free(timesVisited);
	return;
}




