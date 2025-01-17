#include <stdio.h>
#include <stdlib.h>

struct house {
	int x;
	int y;
	long distance;
};

typedef struct house house;

struct list {
	house *houses;
	int N;
};

typedef struct list list;

list parse();
void compute(list);
long findMin(list);

int main(void) {
	list houses;
	houses = parse();
	compute(houses);
	printf("%ld\n", findMin(houses));
	return 0;
}

list parse() {
	int i, N;
	struct house *houses;
	list housesList;
	scanf("%d", &N);
	houses = (struct house*) malloc (sizeof(struct house) * N);
	if (houses == NULL) {
		printf("memory allocation error\n");
		exit(1);
	}
	for (i = 0; i < N; i++) {
		scanf("%d %d", &houses[i].x, &houses[i].y);
	}
	housesList.houses = houses;
	housesList.N = N;
	return housesList;
}

void compute(list housesList) {
	int i, j, N;
	house *houses;
	houses = housesList.houses;
	N = housesList.N;
	for (i = 0; i < N; i++) { // for each student
		for (j = i + 1; j < N; j++) { // compute his distance from all the others
			houses[i].distance = houses[i].distance + abs(houses[i].x - houses[j].x) + abs(houses[i].y - houses[j].y);
			houses[j].distance = houses[j].distance + abs(houses[i].x - houses[j].x) + abs(houses[i].y - houses[j].y);
		}
	}
}
long findMin(list housesList) {
	int i, N;
	long min;
	house *houses;
	houses = housesList.houses;
	N = housesList.N;
	min = houses[0].distance;
	for (i = 1; i < N; i++) {
		if (houses[i].distance < min) {
			min = houses[i].distance;
		}
	}	
	return min;
}






