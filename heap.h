#define N 1000000

int A[N];
int size;

int find_max();
int delete_max();
void insert(int);
void construct_heap(int);
void combine(int);
void combine_up(int);
int max(int, int);
void swap(int*,int*);
