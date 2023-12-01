#include <stdio.h>

char pin(int boolean)
{
	return (boolean) ? 88 : 79;
}

int board[15] = {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1};

void printboard()
{
	printf("____%c____|_._._._.00\n", pin(board[0]));
	printf("___%c_%c___|_._._.01_.02\n", pin(board[1]), pin(board[2]));
	printf("__%c_%c_%c__|_._.03_.04_.05\n", pin(board[3]), pin(board[4]), pin(board[5]));
	printf("_%c_%c_%c_%c_|_.06_.07_.08_.09\n", pin(board[6]), pin(board[7]), pin(board[8]), pin(board[9]));
	printf("%c_%c_%c_%c_%c|10_.11_.12_.13_.14\n", pin(board[10]), pin(board[11]), pin(board[12]), pin(board[13]), pin(board[14]));
	return;
}

int main()
{
	printboard();
}
