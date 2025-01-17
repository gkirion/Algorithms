#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill(int*, int);
void read(int*, int);
void print(int*, int);
int partition(int*, int, int);
void quicksort(int*, int, int);
void swap(int*, int*);

int main(int argc, char **argv) {
	int *A, size = 1000000;
	A = (int*) malloc (size * sizeof (int));
	//fill(A, SIZE);
	read(A, size);
	//print(A, size);
	quicksort(A, 0, size - 1);
	print(A, size);
	free(A);
	return 0;
}

void fill(int *A, int N) {
	int i;
	srand(time(NULL));
	for (i = 0; i < N; i++) {
		A[i] = rand();
	}
}

void read(int *A, int N) {
	int i;
	for (i = 0; i < N; i++) {
		scanf("%d\n", &A[i]);
	}
}

void print(int *A, int N) {
	int i;
	for (i = 0; i < N; i++) {
		printf("%d\n", A[i]);
	}
}

void swap(int *x, int *y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}

int partition(int *A, int left, int right) {
	int middle, pivot, i = left - 1, j = right + 1;
	middle = (left + right) / 2;
	pivot = A[middle];
	while (1) {
	 	while (A[++i] < pivot);
	 	while (A[--j] > pivot);
	 	if (i < j) 
			swap(&A[i], &A[j]);
		else
			return j;
	}
}

void quicksort(int *A, int left, int right) {
	int q;
	if (right <= left) 
		return;
	q = partition(A, left, right);
	quicksort(A, left, q);
	quicksort(A, q + 1, right);
}

