#include "heap.h"

int find_max() {
	if (size <= 0) 
		return -1;	
	return A[0];
}

int delete_max() {
	int max;
	if (size <= 0) 
		return -1;
	max = A[0];
	A[0] = A[size - 1];
	size--;
	combine(0);
	return max;
}

void insert(int e) {
	if (size < N) {
		size++;
		A[size - 1] = e;
		combine_up(size - 1);
	}
}

void combine (int i) {
	int mp = i, left = 2 * i + 1, right = 2 * i + 2;
	if (left < size && A[left] > A[mp]) {
		mp = left;
	}
	if (right < size && A[right] > A[mp]) {
		mp = right;
	}
	if (mp != i) {
		swap(&A[i], &A[mp]);
		combine(mp);
	}
}

void combine_up(int i) {
	if (((i - 1) / 2) >= 0 && A[i] > A[(i - 1) / 2]) {
		swap(&A[i], &A[(i - 1) / 2]);
		combine_up((i - 1) / 2);
	}
}

void construct_heap(int n) {
	int i;	
	size = n;
	for (i = (n - 1) / 2; i >= 0; i--)
		combine(i);
}

int max (int a, int b) {
	return a > b ? a : b;
}

void swap (int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

