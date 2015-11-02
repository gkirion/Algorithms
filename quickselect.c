#include <stdio.h>
#include <stdlib.h>

void read(int*, int);
void print(int*, int);
void swap(int*, int*);
int partition(int*, int, int);
void quicksort(int*, int, int);
int quickselect(int*, int, int, int);

int main(int argc, char **argv) {
	int *A, size, k, elem;
	if (argc != 3) {
		printf("Usage: ./quickselect N (array size) k (K th element)\n");
		return 0;
	}
	size = atoi(argv[1]);
	k = atoi(argv[2]) - 1;
	A = (int*) malloc (size * sizeof(int));
	read(A, size);
	elem = quickselect(A, 0, size - 1, k);
	printf("%d\n", elem);
	/*quicksort(A, 0, size - 1);
	if (A[k] == elem) 
		printf("ok\n");
	else
		printf("not ok\n");*/
	free(A);
	return 0;
}

int quickselect(int *A, int left, int right, int k) {
	int q;
	q = partition(A, left, right);
	if (left == right) 
		return A[left];
	if (k <= q) 
		quickselect(A, left, q, k);
	else
		quickselect(A, q + 1, right, k);
}

void quicksort(int *A, int left, int right) {
	int q;
	if (right <= left) 
		return;
	q = partition(A, left, right);
	quicksort(A, left, q);
	quicksort(A, q + 1, right);
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

