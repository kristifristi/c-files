#include <stdio.h>

int representation[5][5];
int boardchart [15][6][2] = {[0 ... 14][0 ... 5][0 ... 1] = -1};		//position, direction, near/far
int board [15] = {[0 ... 14] = 1};
void printIntArray(int array[], int elems)
{
	for (int i = 0; i < elems - 1; ++i)
	{
		printf("%d, ", array[i]);
	}
	printf("%d", array[elems - 1]);
}

void fillRepresentation()
{
	int position = 0;
	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			 if (j <= i)
			 {
			 	representation[i][j] = position; //puts value of position if it exists
			 	++position;
			 }
			 else
			 {
			 	representation[i][j] = -1;
			 }
		}
	}
}

void fillChart()
{
	int position = 0;
	for(int i = 0; i < 25; ++i)
	{
		position = representation[i/5][i%5];	//gets the value of the position
		if (position == -1) 
		{continue;}	//no chart for impossible board positions
		if (((i % 5) + 1) <= 4)	//makes sure it only looks up (correct) positions inside represention
		{
			boardchart[position][0][0] = representation[(i/5)][(i%5)+1];
			if (representation[(i/5)][(i%5)+1] != -1)
			{boardchart[representation[(i/5)][(i%5)+1]][3][0] = position;}	//writes the opposite direction as well if it exists
			if (((i % 5) + 2) <= 4)
			{
				boardchart[position][0][1] = representation[(i/5)][(i%5)+2];
				if (representation[(i/5)][(i%5)+2] != -1)
				{boardchart[representation[(i/5)][(i%5)+2]][3][1] = position;}
			}
		}
		//second direction
		if ((((i % 5) + 1) <= 4) && (((i / 5) + 1) <= 4))	
		{
			boardchart[position][1][0] = representation[(i/5)+1][(i%5)+1];
			if (representation[(i/5)+1][(i%5)+1] != -1)
			{boardchart[representation[(i/5)+1][(i%5)+1]][4][0] = position;}
			if ((((i % 5) + 2) <= 4) && (((i / 5) + 2) <= 4))
			{
				boardchart[position][1][1] = representation[(i/5)+2][(i%5)+2];
				if (representation[(i/5)+2][(i%5)+2] != -1)
				{boardchart[representation[(i/5)+2][(i%5)+2]][4][1] = position;}
			}
		}
		//third direction
		if (((i / 5) + 1) <= 4)	
		{
			boardchart[position][2][0] = representation[(i/5)+1][(i%5)];
			if (representation[(i/5)+1][(i%5)] != -1)
			{boardchart[representation[(i/5)+1][(i%5)]][5][0] = position;}
			if (((i / 5) + 2) <= 4)
			{
				boardchart[position][2][1] = representation[(i/5)+2][(i%5)];
				if (representation[(i/5)+2][(i%5)] != -1)
				{boardchart[representation[(i/5)+2][(i%5)]][5][1] = position;}
			}
		}
	}
}

char pin(int boolean)//for visuals
{
	return (boolean) ? 88 : 79;
}

void printboard()//does what it says on the tin
{
	printf("    %c    |        01\n", pin(board[0]));
	printf("   %c %c   |      02  03\n", pin(board[1]), pin(board[2]));
	printf("  %c %c %c  |    04  05  06\n", pin(board[3]), pin(board[4]), pin(board[5]));
	printf(" %c %c %c %c |  07  08  09  10\n", pin(board[6]), pin(board[7]), pin(board[8]), pin(board[9]));
	printf("%c %c %c %c %c|11  12  13  14  15\n", pin(board[10]), pin(board[11]), pin(board[12]), pin(board[13]), pin(board[14]));
	return;
}


int domove(int origin, int destination)		//returns 0 on valid move and advances board, otherwise returns error value
{
	int direction = -1;
	if(((origin < 0) || (origin > 14)) || ((destination < 0) || (destination > 14)))	//is the move on the board?
	{return 1;}
	for (int i = 0; i < 6; ++i)
	{
		direction = (boardchart[origin][i][1] == destination) ? i : direction;		//finds the direction of the move
	}
	//printf("direction = %d,", direction); //debug
	if (direction == -1)		//does the move exist?
	{return 2;}
	int passover = boardchart[origin][direction][0];
	//printf("passover = %d\n", passover); //debug
	//printf("movestatus: %d %d %d\n", board[origin], board[passover], board[destination]); //debug
	if ((board[origin] == 0) || ((board[passover] == 0) || (board[destination] == 1)))	//can the move be played?
	{return 3;}
	board[origin] = 0;
	board[passover] = 0;
	board[destination] = 1;
	return 0;
}
void gameloop()
{
	int moveOrigin;
	int moveDestination;
	int winstate = 0;
	int pegCount = 14;
	while(1)
	{
		printboard();
		printf("next move or quit with \"-1 -1\": ");
		scanf("%d %d", &moveOrigin, &moveDestination);
		if ((moveOrigin == -1) && (moveDestination == -1))
		{break;}
		switch(domove(moveOrigin - 1, moveDestination - 1))
		{
			case 1:
				printf("\n\amove out of bounds!\n");
				break;
			case 2:
				printf("\n\amove does not exist!\n");
				break;
			case 3:
				printf("\n\amove can not be played!\n");
				break;
			default:
				--pegCount;
		}
		if(pegCount == 1)
		{
			winstate = 1;
			break;
		}
	}
	if (winstate == 1)
	{
		printboard();
		printf("You won! Well done! :)\n");
	}
	else
	{
		printf("%d pegs left. Better luck next time!\n", pegCount);
	}
}

void startgame()
{
	int start;
	printboard();
	while (1)
	{
		printf("choose a starting position: ");
		scanf("%d", &start);
		if ((start > 0) && (start < 16))
		{
			break;
		}
		else
		{
			printf("\abad starting position!\n");
		}	
	}
	board[start - 1] = 0;	
	gameloop();
}

int main()
{
	fillRepresentation();
	fillChart();
	/*printf("representation of the board:\n");
	for (int i = 0; i < 5; ++i)
	{
		printIntArray(representation[i], 5);
		printf("\n");
	}
	printf("chart used to validate moves:\n");
	for (int i = 0; i < 16 - 1; ++i)
	{
		printf("%d: ", i);
		for (int j = 0; j < 5; ++j)
		{
			printf("%d, ", boardchart[i][j][0]);
		}
		printf("%d\n", boardchart[i][5][0]);
	}
	printf("\n");
	for (int i = 0; i < 15; ++i)
	{
		printf("%d: ", i);
		for (int j = 0; j < 5; ++j)
		{
			printf("%d, ", boardchart[i][j][1]);
		}
		printf("%d\n", boardchart[i][5][1]);
	} */ //debug
	startgame();
	return 0;
}
