#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct edge {
	int src;
	int dest;
	int weight;
};

struct node {
	int v;
	int w;
	struct node *next;
};

struct list {
	int size;
	struct node *head;
};

struct graph {
	int V;
	struct list *adj;
};

void swap(struct edge*, struct edge*);
int partition(struct edge*, int, int);
void quicksort(struct edge*, int, int);
int find(int*, int);
void unite(int*, int*, int, int);
void list_init(struct list*);
void list_add(struct list*, int, int);
void graph_init(struct graph*, int);
void add_edge(struct graph*, int, int, int);
void print_graph(struct graph*);
void compute_mst(struct graph*, struct edge*, int, int);
void compute_bottlenecks(struct graph*, int*);
void dfs(struct graph*, int, int, bool*, int*, int);
int max(int, int);


int main(void) {
	int i, N, M, Q, *bottleneck;
	struct edge *E, *dist;
	struct graph G;
	scanf("%d %d", &N, &M);
	E = (struct edge*) malloc (M * sizeof(struct edge));
	for (i = 0; i < M; i++) { // get edges
		scanf("%d %d %d", &E[i].src, &E[i].dest, &E[i].weight);
	}
	scanf("%d", &Q);
	dist = (struct edge*) malloc (Q * sizeof(struct edge));
	for (i = 0; i < Q; i++) { // get trips
		scanf("%d %d", &dist[i].src, &dist[i].dest);
	}
	compute_mst(&G, E, M, N);
	bottleneck = (int*) malloc (N * N * sizeof(int));
	compute_bottlenecks(&G, bottleneck); // find bottleneck of each pair of nodes
	for (i = 0; i < Q; i++) {
		printf("%d\n", bottleneck[(dist[i].src - 1) * N + (dist[i].dest - 1)]);
	}
	free(bottleneck);
	free(dist);
	free(E);
	return 0;
}

void swap(struct edge *x, struct edge *y) {
	struct edge temp = *x;
	*x = *y;
	*y = temp;
}

int partition(struct edge *E, int left, int right) {
	int middle, pivot, i = left - 1, j = right + 1;
	middle = (left + right) / 2;
	pivot = E[middle].weight;
	while (1) {
	 	while (E[++i].weight < pivot);
	 	while (E[--j].weight > pivot);
	 	if (i < j) 
			swap(&E[i], &E[j]);
		else
			return j;
	}
}

void quicksort(struct edge *E, int left, int right) {
	int q;
	if (right <= left) 
		return;
	q = partition(E, left, right);
	quicksort(E, left, q);
	quicksort(E, q + 1, right);
}

int find(int *rep, int i) {
	if (rep[i] == i)
		return i;
	rep[i] = find(rep, rep[i]);
	return rep[i];
}

void unite(int *rep, int *rank, int x, int y) {
	int repx = find(rep, x);
	int repy = find(rep, y);
	if (rank[repx] > rank[repy]) {
		rep[repy] = repx;
	}
	else if (rank[repx] < rank[repy]) {
		rep[repx] = repy;
	}
	else {
		rep[repy] = repx;
		rank[repx]++;
	}
}

void list_init(struct list *list) {
	list->size = 0;
	list->head = NULL;
}

void list_add(struct list *list, int v, int w) {
	struct node *node;
	node = (struct node*) malloc (sizeof(struct node));
	node->v = v;
	node->w = w;
	node->next = list->head;
	list->head = node;
	list->size++;
}

void graph_init(struct graph *graph, int v) {
	int i;	
	graph->V = v;
	graph->adj = (struct list*) malloc (v * sizeof(struct list));
	for (i = 0; i < v; i++) {
		list_init(&graph->adj[i]);
	}
}

void add_edge(struct graph *graph, int u, int v, int w) {
	list_add(&graph->adj[u], v, w);
	list_add(&graph->adj[v], u, w);
}

void print_graph(struct graph *graph) {
	int i, n;
	struct node *node;
	n = graph->V;
	for (i = 0; i < n; i++) {
		printf("neighbors of %d: ", i);
		node = graph->adj[i].head;
		while (node != NULL) {
			printf("%d ", node->v);
			node = node->next;
		}
		printf("\n");
	}
}

void compute_mst(struct graph *G, struct edge *E, int M, int N) {
	int *rep, *rank, i, x, y;	
	quicksort(E, 0, M - 1); // sort edges, ascending order
	rep = (int*) malloc (N * sizeof(int)); // representative of each node 
	rank = (int*) malloc (N * sizeof(int)); // rank of each union
	graph_init(G, N);
	for (i = 0; i < N; i++) {
		rep[i] = i;
		rank[i] = 1;
	}
	for (i = 0; i < M; i++) {
		x = find(rep, E[i].src - 1);
		y = find(rep, E[i].dest - 1);
		if (x != y) {
			unite(rep, rank, x, y);
			add_edge(G, E[i].src - 1, E[i].dest - 1, E[i].weight);
		}
	}
	free(rep);
	free(rank);
}

void compute_bottlenecks(struct graph *graph, int *bottleneck) {
	int i, j, n;
	bool *visited;
	n = graph->V;
	visited = (bool*) malloc(n * sizeof(bool));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			visited[j] = false;
		} 
		dfs(graph, i, i, visited, bottleneck, 0);
	}
	free(visited);
}

void dfs(struct graph *graph, int u, int v, bool *visited, int *bottleneck, int curr_max) {
	struct node *node = graph->adj[v].head;
	int n = graph->V;
	if (visited[v]) return;
	visited[v] = true;
	while (node != NULL) {
		if (!visited[node->v]) {
			bottleneck[u * n + node->v] = max(curr_max, node->w);
			dfs(graph, u, node->v, visited, bottleneck, bottleneck[u * n + node->v]);
		}
		node = node->next;
	}
}

int max(int a, int b) {
	if (a > b)
		return a;
	return b;
}







