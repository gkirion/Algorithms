#include <stdio.h>

#define N 1000000

typedef int datatype;

struct elem {
	datatype value;
	int index;
	int rep;
	int size;
};

struct elem A[N];

struct elem find(struct elem x) {
	int index = x.index;
	while (index != A[index].rep) {
		index = A[index].rep;
	}
	return A[index];
}

struct elem find_and_compress(struct elem x) {
	int index = x.index;
	if (index != A[index].rep) {
		A[index].rep = find_and_compress(A[x.rep]).rep;
	}
	return A[index];
}

void unite(struct elem x, struct elem y) {
	if (x.rep == y.rep) return;
	if (A[x.rep].size > A[y.rep].size) {
		A[x.rep].size = A[x.rep].size + A[y.rep].size;
		A[y.rep].rep = x.rep;
	}
	else {
		A[y.rep].size = A[y.rep].size + A[x.rep].size;
		A[x.rep].rep = y.rep;
	}
}

int main(void) {
	int i;
	for (i = 0; i < N; i++) {
		A[i].rep = i;
		A[i].value = i;
		A[i].index = i;
		A[i].size = 1;
	}
	printf("%d\n", find(A[499]).value);
	printf("%d\n", find(A[499]).size);
	unite(A[499], A[500]);
	printf("%d\n", find(A[499]).value);
	printf("%d\n", find(A[499]).size);
	unite(A[600], A[601]);
	unite(A[499], A[600]);
	unite(A[700], A[800]);
	unite(find(A[499]), find(A[800]));
	printf("%d\n", A[499].rep);
	printf("%d\n", find_and_compress(A[499]).value);
	printf("%d\n", find(A[499]).size);
	printf("%d\n", A[499].rep);
	printf("%d\n", A[700].rep);
	find_and_compress(A[700]);
	printf("%d\n", A[700].rep);
	return 0;
}

