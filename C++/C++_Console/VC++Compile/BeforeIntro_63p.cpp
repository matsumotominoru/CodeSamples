#include <stdio.h>
#include <stdlib.h>
int factorial(int n);
int main(int argc, char *argv[])
{
	int x, n;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s number\n", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);
	x = factorial(n);
	printf("%d! = %d\n", n, x);
	return 0;
}

int factorial(int n) {
	int i, x = 1;
	for ( i = 2; i <= n; i++)
	{
		x *= i;
	}
	return x;
}
