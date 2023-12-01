//Kristiaan Cramer 2023
//header file for using style.c library(duh)
//made using info available at: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

//macros for use with textStyle()
#define RESET_ALL 0
#define BOLD 1
#define RESET_BOLD 22
#define RESET_DIM 22
#define DIM 2
#define ITALIC 3
#define RESET_ITALIC 23
#define UNDERLINE 4
#define RESET_UNDERLINE 24
#define BLINKING 5
#define RESET_BLINKING 25
#define INVERSE 7
#define REVERSE 27
#define STRIKETHROUGH 9
#define RESET_STRIKETHROUGH 29
#define INVISIBLE 8
#define RESET_INVISIBLE 29
#define BLACK 90
#define BG_BLACK 100
#define RED 91
#define BG_RED 101
#define GREEN 92
#define BG_GREEN 102
#define YELLOW 93
#define BG_YELLOW 103
#define BLUE 94
#define BG_BLUE 104
#define MAGENTA 95
#define BG_MAGENTA 105
#define CYAN 96
#define BG_CYAN 106
#define WHITE 97
#define BG_WHITE 107

void clrScreen();
void pushprint(); //forces the program to print to stdout
void ResetCursor();
void MoveCursor(unsigned int line, unsigned int col);
void setTxtStyle(unsigned int id);
void setTxtColor255(unsigned id);	//for information on color ids, visit the website
void setBGColor255(unsigned id);
void setTxtColorRGB(unsigned r, unsigned g, unsigned b);
void setBGColorRGB(unsigned r, unsigned g, unsigned b);
void hideCursor();
void showCursor();

struct RGB	//useful when working with colors :)
{
	unsigned r;
	unsigned g;
	unsigned b;
};
