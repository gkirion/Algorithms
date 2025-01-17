#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int n;

bool hamiltonian(bool *adj, int *path, bool *visited, int pos, int v) {
	if (pos == n) {
		if (adj[path[pos - 1] * n + path[0]])
			return true;
		else
			return false;
	}
	for (int i = 1; i < n; i++) {
		if (adj[(pos - 1) * n + i] && !visited[i]) {
			path[pos] = i;
			visited[i] = true;
			if (hamiltonian(adj,path,visited,pos + 1, i))
				return true;
			path[pos] = -1;
			visited[i] = false;
		}
	}
	return false;
}

bool *create_graph(int n) {
	bool *adj;
	adj = (bool*) malloc (n * n * sizeof(bool));
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adj[i * n + j] = rand() % 2;
	return adj;
}

bool is_hamiltonian(bool *adj) {
    bool *visited;
    visited = (bool*) malloc (n * sizeof(bool));
    visited[0] = true;
    for (int i = 1; i < n; i++)
    	visited[i] = false;
	int *path;
	path = (int*) malloc (n * sizeof(int));
	path[0] = 0;
	for (int i = 1; i < n; i++)
		path[i] = -1;
	return hamiltonian(adj,path,visited,1,0);
}

bool *parse() {
	bool *adj;
	scanf("%d\n", &n);
	adj = (bool*) malloc (n * n * sizeof(bool));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &adj[i * n + j]);
	return adj;		
}



int main(void) {
	bool *adj;
	adj = parse();
	//adj = create_graph(n);
	if (is_hamiltonian(adj))
		printf("hamiltonian cycle exists!\n");
	else 
		printf("hamiltonian cycle doesn't exists!\n");
	return 0;	
}
