#include <stdio.h>
#include <stdlib.h>

void fill(int*, int);
void fill_range(int*, int, int, int);
void print(int*, int);

int main(int argc, char **argv) {
	int *A;
	if (argc != 2 && argc != 4) {
		printf("Usage: ./rgen n (numbers) (from) x (to) y (x and y are optional)\n");
		return 0;
	}
	else {
		A = (int*) malloc (atoi(argv[1]) * sizeof (int));
		if (argc == 2)
			fill(A, atoi(argv[1]));
		else
			fill_range(A, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	}
	print(A, atoi(argv[1]));
	free(A);
	return 0;
}

void fill(int *A, int n) {
	int i;
	srand(time(NULL));
	for (i = 0; i < n; i++) {
		A[i] = rand();
	}
}

void fill_range(int *A, int n, int x, int y) {
	int i;
	srand(time(NULL));
	for (i = 0; i < n; i++) {
		A[i] = rand() % (y - x + 1) + x;
	}
}

void print(int *A, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d\n", A[i]);
	}
}
