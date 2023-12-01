//Kristiaan Cramer 2023
//a list of macros to manipulate the visuals in the terminal
#include <stdio.h>

void clrScreen()
{
	printf("\033[2J");
	return;
}

void pushprint()//handig als je met intervals wil printen zonder NL
{
	fflush(stdout);
	return;
}

void resetCursor()
{
	printf("\033[H");
}

void moverCursor(unsigned line, unsigned col)
{
	printf("\033[%u;%uH",line ,col);
	return;
}

void setTxtStyle(unsigned int id) //style macros can be found in header
{
	printf("\033[%um",id);
	return;
}

void setTxtColor255(unsigned id) //apparantly there are 256 predefined colors terminals just have
{
	printf("\033[38;5;%um",id);
	return;
}

void setBGColor255(unsigned id)
{
	printf("\033[48;5;%um",id);
	return;
}

void setTxtColorRGB(unsigned r, unsigned g, unsigned b)
{
	printf("\033[38;2;%u;%u;%um", r, g, b);
	return;
}

void setBGColorRGB(unsigned r, unsigned g, unsigned b)
{
	printf("\033[48;2;%u;%u;%um", r, g, b);
	return;
}

void hideCursor()
{
	printf("\033[?25l");
	return;
}

void showCursor()
{
	printf("\033[?25h");
	return;
}
