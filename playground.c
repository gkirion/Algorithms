#include <stdio.h>
#include <stdlib.h>

void read(int*, int);
//long find_places(int*, int, int);
long find_places(int*, int, int);
void zerofill(int*, int);
int compute_column(int*, int, int, int, int);

int main(void) {
	int *A, size, k;
	long c;
	scanf("%d %d\n", &size, &k);
	A = (int*) malloc (size * size * sizeof(int));
	read(A, size);
	c = find_places(A, size, k);
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

/*
long find_places(int *A, int N, int k) {
	int a, b, i, j, t, m;
	long c = 0;
	for (a = 0; a < N; a++) {
		for (b = 0; b < N; b++) {
			for (i = a; i < N; i++) {
				t = 0;
				for (j = b; j < N; j++) {
					for (m = i; m >= a; m--) {
						if (A[m * N + j] == 1) t++;
					}
					if (t == k) c++; else if (t > k) break;
				}
			}
		}
	}
	return c;
}*/

long find_places (int *A, int N, int k) {
	int *C, a, b, i, j, t, s, prev, col;
	long c = 0, tc = 0;
	C = (int*) malloc (N * sizeof(int));
	for (a = 0; a < N; a++) {
		zerofill(C, N);
		for (i = a; i < N; i++) {
			for (b = 0; b < N; b++) {
				if (b == 0 || j <= b) { 
					s = b; t = 0; tc = 0;
					if (b > 0 && j == b) C[j] -= A[i * N + j];
				}
				else {
					prev = C[b - 1];
					if (prev > 0) {
						s = j; t = t - col - prev; tc = 0;
						if (j < N) C[j] -= A[i * N + j];
					}
					else {
						c += tc; continue;
					}
				}
				for (j = s; j < N; j++) {
					C[j] += A[i * N + j];
					col = C[j];
					t += C[j];
					if (t == k) tc++; else if (t > k) break;
				}
				c += tc;
			}
		}
	}
	free(C);
	return c;
}

int compute_column(int *A, int N, int i, int a, int j) {
	int m, c = 0;
	for (m = i; m >= a; m--) {
		c += A[m * N + j];
	}
	return c;
}


/*
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
*/

void zerofill(int *A, int N) {
	int i;
	for (i = 0; i < N; i++) { 
		A[i] = 0;
	}
}


void read(int *A, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			A[i * n + j] = getchar() - '0';
		}
		getchar();
	}
}
