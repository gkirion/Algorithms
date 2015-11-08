#include <stdio.h>
#include <stdlib.h>

struct result {
	int *S;
	int *F;
	int N;
	long K;
};

typedef struct result result;

result parse() {
	int i, N;
	long K;
	result res;
	scanf("%d %ld", &N, &K);
	res.S = (int*) malloc (N * sizeof(int));
	if (res.S == NULL) {
		printf("memory allocation error\n");
		exit(1);
	}
	res.F = (int*) malloc (N * sizeof(int));
	if (res.F == NULL) {
		printf("memory allocation error\n");
		exit(1);
	}
	for (i = 0; i < N; i++) {
		scanf("%d %d", &res.S[i], &res.F[i]);
	}
	res.N = N;
	res.K = K;
	return res;
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

int findTime(int *S, int *F, int N, long K) {
	int i, j, a, b, flow, lost, time;
	long work;
	work = 0;
	flow = 1;
	a = S[0];
	i = 1;
	j = 0;
	lost = 0;
	while ((i < N || j < N) && (work < K)) {
		if ((i < N) && (S[i] < F[j])) {
			b = S[i];
			work = work + (b - a + 1) * flow;
			if (lost > flow)
				work = work + lost - flow;
			if (work >= K)
				time = b - (work - K) / flow;
			else 
				work = work - flow;
			lost = flow;
			flow++;
			i++;
		}
		else {
			b = F[j];
			work = work + (b - a + 1) * flow;
			if (lost > flow)
				work = work + lost - flow;
			if (work >= K)
				time = b - (work - K) / flow;
			else
				work = work - flow;
			lost = flow;
			flow--;
			j++;
		}
		a = b;
	}
	return time;
}

int main(void) {
	result res;
	res = parse();
	quicksort(res.S,0,res.N - 1);
	quicksort(res.F,0,res.N - 1);
	printf("%d\n", findTime(res.S, res.F, res.N, res.K));
	return 0;
}



