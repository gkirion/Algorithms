#include <stdio.h>
#include "heap.h"

void fill(int*, int);
void read(int*, int);
void print(int*, int);
void heapsort(int);

int main(void) {
	int i;
	//fill(A, 1000000);
	read(A, N);
	heapsort(1000000);
	print(A, 1000000);
}

void fill(int *A, int n) {
	int i;
	srand(time(NULL));
	for (i = 0; i < n; i++) {
		A[i] = rand();
	}
}

void read(int *A, int n) {
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d\n", &A[i]);
	}
}

void print(int *A, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d\n", A[i]);
	}
}

void heapsort(int n) {
	int i, e;
	construct_heap(n);
	for (i = n - 1; i >= 0; i--) {
		e = delete_max();
		A[i] = e;
	}
}
