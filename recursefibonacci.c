#include <stdio.h>

unsigned long fib(unsigned long old, unsigned long cur, unsigned long step)
{
	printf("%lu\n", cur);
	return (step == 0) ? cur : fib(cur, old + cur, --step);
}

unsigned long fibHelp(unsigned long steps)
{
	return fib(0, 1, steps);
}

void main()
{
	fibHelp(100);
	return;
}
