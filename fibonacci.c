#include <stdio.h>

#define MAX 100

void init(long *A, int N) {
	int i;
	for (i = 0; i < N; i++) {
		A[i] = -1;
	}
}

int fib(int n) {
	if (n <= 1)
		return n;
	return fib(n - 1) + fib(n - 2);
}

long memfib(long *A, int n) {
	if (A[n] == -1) {
		if (n <= 1)
			A[n] = n;
		else 
			A[n] = memfib(A, n - 1) + memfib(A, n - 2);
	}
	return A[n];		
}

int main(void) {
	long A[MAX];
	init(A, MAX);
	printf("%ld\n", memfib(A, 50));
	return 0;
}
