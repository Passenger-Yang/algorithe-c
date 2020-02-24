#include <stdio.h>

/* fact */
int fact(int n)
{
	if(n < 0)
		return 0;
	else if(n == 0)
		return 1;
	else if(n == 1)
		return 1;
	else
		return n * fact(n - 1);
}

/* compute a factorial in a tail-recursive manner */
int facttail(int n, int a)
{
	if(n < 0)
		return 0;
	else if(n == 0)
		return 1;
	else if(n == 1)
		return a;
	else
		return facttail(n - 1, n * a);
}


int main(void)
{
	printf("recuursive:%d\n", fact(4));
	printf("tail-recursive:%d\n", facttail(4, 1));

	return 0;
}



