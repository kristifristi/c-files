#include <stdio.h>

int simpleInterest(int principalAmount,int time,int rate)
{
	return principalAmount * time * rate / 100;
}

int main()
{
	int p;		//shut the depths your mouth
	int t;
	int r;
	
	printf("Principal Amount in cents: ");
	scanf("%d", &p);
	printf("Time: ");
	scanf("%d", &t);
	printf("Rate in percent: ");
	scanf("%d", &r);
	
	printf("Interest: %d\n", simpleInterest(p, t, r));
	return 0;
}
