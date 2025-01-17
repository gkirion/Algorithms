#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct vertex {
	int v;
	struct vertex *next;
	struct vertex *rep;
	struct _union *u;
};

struct edge {
	struct vertex *u;
	struct vertex *v;
	int until;
};

struct node {
	struct edge *e;
	struct node *next;
};

struct graph {
	struct vertex *V;
	struct edge *E;
	int N; // number of verteces
	int M; // number of edges
};

struct result {
	struct graph G;
	int K; // number of works
};

struct info {
	struct _union *u;
	struct vertex *rep;
};

struct _union {
	struct vertex *head;
	struct vertex *tail;
	struct info;
	int size;
};


struct node *list_add(struct node *head, struct edge *e) {
	struct node *n;
	n = (struct node*) malloc (sizeof(struct node));
	n->e = e;
	n->next = head;
	return n;
}

struct result parse() {
	int N, M, K, i, u, v, until;
	struct result res;
	struct graph G;
	struct vertex *V;
	struct edge *E;
	scanf("%d %d %d", &N, &M, &K);
	V = (struct vertex*) malloc (N * sizeof(struct vertex));
	E = (struct edge*) malloc (M * sizeof(struct edge));
	for (i = 0; i < N; i++) {
		V[i].v = i + 1;
	}
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &v, &until);
		E[i].u = &V[u - 1];
		E[i].v = &V[v - 1];
		E[i].until = until;
	}
	G.V = V;
	G.E = E;
	G.N = N;
	G.M = M;
	res.G = G;
	res.K = K;
	return res;
}

void swap(struct edge *A, int x, int y) {
	struct edge temp = A[x];
	A[x] = A[y];
	A[y] = temp;
}

int partition(struct edge *A, int left, int right) {
	int middle, pivot, i = left - 1, j = right + 1;
	middle = (left + right) / 2;
	pivot = A[middle].until;
	while (1) {
	 	while (A[++i].until > pivot);
	 	while (A[--j].until < pivot);
	 	if (i < j) 
	 		swap(A, i, j);
	 	else
	 		return j;
	}
}

void quicksort(struct edge *A, int left, int right) {
	int q;
	if (right <= left) 
		return;
	q = partition(A, left, right);
	quicksort(A, left, q);
	quicksort(A, q + 1, right); 
}

struct _union *union_create(struct vertex *v) {
	struct _union *u;
	u = (struct _union*) malloc (sizeof(struct _union));
	u->head = v;
	u->tail = v;
	u->size = 1;
	v->next = NULL;
	v->rep = v;
	v->u = u;
	return u;
}

struct vertex *union_find(struct vertex *v) {
	return v->rep;
}

struct _union *union_merge(struct vertex *v1, struct vertex *v2) {
	struct vertex *v;
	struct _union *u1, *u2, *temp;
	u1 = v1->rep->u;
	u2 = v2->rep->u;
	if (u1->size < u2->size) {
		temp = u1;
		u1 = u2;
		u2 = temp;
	}
	u1->tail->next = u2->head;
	u1->tail = u2->tail;
	v = u2->head;
	while (v != NULL) {
		v->rep = u1->head;
		v = v->next;
		(u1->size)++;
	}
	free(u2);
	return u1;
}

struct node *compute_mst(struct graph *G) {
	int i;
	struct node *edge = NULL;
	struct vertex *V = G->V;
	struct edge *E = G->E;
	quicksort(G->E, 0, G->M);
	for (i = 0; i < G->N; i++)
		union_create(&V[i]);
	for (i = 0; i < G->M; i++) {
		if (union_find(E[i].u) != union_find(E[i].v)) {
			union_merge(E[i].u, E[i].v);
			edge = list_add(edge, &E[i]);
		}
	}
	return edge;
}



void findT(struct result res) {
	int works;
	struct node *edge;
	edge = compute_mst(&res.G);
	works = 0;
	while (edge != NULL && works < res.K) { // when there are still roads to repair and works to be done
		edge->e->until = INT_MAX;
		edge = edge->next;
		works++;
	}
	if (edge == NULL) { // if all roads repaired
		printf("infinity\n");
	}
	else {
		printf("%d\n", edge->e->until);
	}
}



int main(void) {
	struct result res;
	res = parse();
	findT(res);
	return 0;
}
