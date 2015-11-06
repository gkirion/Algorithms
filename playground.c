#include <stdio.h>
#include <stdlib.h>

void read(int*, int);
long find_places(int*, int, int);

int main(void) {
	int *A, size;
	long c;
	scanf("%d\n", &size);
	A = (int*) malloc (size * sizeof(int));
	read(A, size);
	c = find_places(A, size, 1000);
	printf("%ld\n", c);
	free(A);
	return 0;
}
/*
long find_places(int *A, int N, int k) {
	int i, j, t;
	long c = 0;
	for (i = 0; i < N; i++) {
		t = 0;
		for (j = i; j < N; j++) {
			if (A[j] == 1) t++;
			if (t == k) c++; else if (t > k) break; 
		}
	}
	return c;
}*/
/*
long find_places(int *A, int N, int k) {
	int i, j, t, s;
	long c = 0;
	for (i = 0; i < N; i++) {
		if (i > 0 && A[i - 1] == 1) {s = j; t = k - 1;} else {s = i; t = 0;} 
		for (j = s; j < N; j++) {
			if (A[j] == 1) t++;
			if (t == k) c++; else if (t > k) break; 
		}
	}
	return c;
}*/



long find_places(int *A, int N, int k) {
	int i, j, t, s;
	long c = 0, tc = 0;
	for (i = 0; i < N; i++) {
		if (i > 0) {
			if (A[i - 1] == 1) {s = j; t = k - 1; tc = 0;} else {c += tc; continue;}
		}
		else {s = i; t = 0; tc = 0;}
		for (j = s; j < N; j++) {
			if (A[j] == 1) t++;
			if (t == k) tc++; else if (t > k) break;
		}
		c = c + tc;
	}
	return c;
}


void read(int *A, int n) {
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d\n", &A[i]);
	}
}
