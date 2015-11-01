#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000

void fill(int*, int);
void read(int*, int);
void print(int*, int);
void quicksort(int*, int, int);
int partition(int*, int, int);
void swap(int*, int, int);

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

void swap(int *A, int x, int y) {
	int temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}

int partition(int *A, int left, int right) {
	int middle, pivot, i = left - 1, j = right + 1;
	middle = (left + right) / 2;
	pivot = A[middle];
	while (1) {
	 	while (A[++i] < pivot);
	 	while (A[--j] > pivot);
	 	if (i < j) 
	 		swap(A, i, j);
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

int main(void) {
	int *A;
	A = (int*) malloc (SIZE * sizeof (int));
	//fill(A, SIZE);
	read(A, SIZE);
	//print(A, SIZE);
	quicksort(A, 0, SIZE - 1);
	print(A, SIZE);
	return 0;
}
