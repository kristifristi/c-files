#include <stdio.h>

int layer = 0;
int iteration = 0;
int ack(unsigned int m,unsigned int n)
{
	unsigned ret;
	printf("m=%u\tn=%u\ti=%u\tl=%d\n", m, n, iteration, layer);
	layer++;
	iteration++;
	if (m == 0)
	{
		ret = n + 1;
	}
	else
	{	
		if (n == 0)
		{
			ret = ack(m-1,1);
		}
		else
		{
			ret = ack(m-1, ack(m, n-1));
		}
	}
	printf("return: %u\n", ret);
	layer--;
	return ret;
	
}


int main(int argc, char* argv[])
{
	unsigned int n;
	unsigned int m;
	if (argc == 3)
	{
		sscanf(argv[1], "%u", &m);
		sscanf(argv[2], "%u", &n);
		printf("result:%u\n", ack(m,n));
	}
	else
	{
		printf("requires two positive or zero integers!\n\a");
	}
}
