#include <stdio.h>
#include <stdlib.h>

struct interval {
	int s;
	int f;
	long flow;
};

struct node {
	struct interval data;
	struct node *left;
	struct node *right;
	int height;
};

struct result {
	struct node *intervals;
	long K;
};

typedef struct result result;
int compute_height(struct node*);
int compute_balance(struct node*);
struct node *rotate_left(struct node*);
struct node *rotate_right(struct node*);
struct node *check_balance(struct node*);
struct node *split(struct node*, struct interval);
struct node *insert_node(struct node*, struct interval);
void print_postorder(struct node*);
void print_inorder(struct node*);
void print_preorder(struct node*);
int max_height(struct node*, struct node*);
struct node *delete_node(struct node*, struct interval);
int find_time(struct node*, long*, long K);
result parse();


int compute_height(struct node *root) {
	int height, left_height, right_height;
	if (root->left != NULL) {
		left_height = root->left->height;
	}
	else {
		left_height = -1;
	}
	if (root->right != NULL) {
		right_height = root->right->height;
	}
	else {
		right_height = -1;
	}
	height = left_height;
	if (right_height > height) {
		return right_height;
	}
	return height;
}

int compute_balance(struct node *root) {
	int balance_factor, left_height, right_height;
	if (root->left != NULL) {
		left_height = root->left->height;
	}
	else {
		left_height = -1;
	}
	if (root->right != NULL) {
		right_height = root->right->height;
	}
	else {
		right_height = -1;
	}
	balance_factor = left_height - right_height;
	return balance_factor;
}

struct node *rotate_left(struct node *root) {
	int balance_factor;
	struct node *right_child = root->right;
	root->right = right_child->left;
	right_child->left = root;
	balance_factor = compute_balance(root);
	if (balance_factor == -2) {
		root->height = root->height - 2;
	}
	else {
		(root->height)--;
		(right_child->height)++;
	}
	return right_child;
}

struct node *rotate_right(struct node *root) {
	int balance_factor;
	struct node *left_child = root->left;
	root->left = left_child->right;
	left_child->right = root;
	balance_factor = compute_balance(root);
	if (balance_factor == 2) {
		root->height = root->height - 2;
	}
	else {
		(root->height)--;
		(left_child->height)++;
	}
	return left_child;
}

struct node *check_balance(struct node *root) {
	int balance_factor;
	balance_factor = compute_balance(root);
	if (balance_factor == 2) {
		balance_factor = compute_balance(root->left);
		if (balance_factor == -1) {
			root->left = rotate_left(root->left);
		}
		return rotate_right(root);
	}
	else if (balance_factor == -2) {
		balance_factor = compute_balance(root->right);
		if (balance_factor == 1) {
			root->right = rotate_right(root->right);
		}
		return rotate_left(root);
	}
	return root;
}


struct node *split(struct node *root, struct interval element) {
	struct interval new, old, temp;
	old = root->data;
	root = delete_node(root, root->data);
	if (old.s > element.s) {
   	}
   	else {
   		temp = old;
   		old = element;
   		element = temp;
   	}	
    new.s = element.s;
    new.f = old.s - 1;
    new.flow = element.flow;
    if (new.f - new.s >= 0) { // first interval
    	root = insert_node(root, new);
    }
    new.s = old.s;
    if (old.f > element.f) {
    	new.f = element.f;
    	new.flow = element.flow + old.flow;
    	if (new.f - new.s >= 0) { // second interval
    		root = insert_node(root, new);
    	}
    	new.s = element.f + 1;
    	new.f = old.f;
    	new.flow = old.flow;
    	if (new.f - new.s >= 0) { // third interval
    		root = insert_node(root, new);
    	}
    }	
    else {
    	new.f = old.f;
    	new.flow = element.flow + old.flow;
    	if (new.f - new.s >= 0) { // second interval
    		root = insert_node(root, new);
    	}
    	new.s = old.f + 1;
    	new.f = element.f;
    	new.flow = element.flow;
    	if (new.f - new.s >= 0) { // third interval
    		root = insert_node(root, new);
    	}
    }
    return root;
}

struct node *insert_node(struct node *root, struct interval element) {
    if (root == NULL) {
        root = (struct node*) malloc (sizeof(struct node));
        if (root == NULL) {
            printf("could not allocate memory, exiting...\n");
            exit(-1);
        }
        root->data = element;
		root->height = 0;
        root->left = NULL;
        root->right = NULL;
       
    }
    else if (root->data.s > element.f) {
        root->left = insert_node(root->left, element);
		root->height = max_height(root->left, root->right) + 1;
		root = check_balance(root);
    }
    else if (root->data.f < element.s) {
        root->right = insert_node(root->right, element);
		root->height = max_height(root->left, root->right) + 1;
		root = check_balance(root);
    }
    else {
    	root = split(root, element);
    }
    return root;
}

void print_postorder(struct node *root) {
    if (root != NULL) {
        print_postorder(root->left);
        print_postorder(root->right);
        printf("%d-%d\n", root->data.s, root->data.f);
    }
}

void print_inorder(struct node *root) {
    if (root != NULL) {
        print_inorder(root->left);
        printf("%d %d %ld\n", root->data.s, root->data.f, root->data.flow);
        print_inorder(root->right);
    }
}

int count_nodes(struct node *root) {
	if (root == NULL)
		return 0;
	return 1 + count_nodes(root->left) + count_nodes(root->right);
}

void print_preorder(struct node *root) {
    if (root != NULL) {
        printf("%d-%d\n", root->data.s, root->data.f);
        print_preorder(root->left);
        print_preorder(root->right);
    }
}

int max_height(struct node *ltree, struct node *rtree) {
	int max;
	if (ltree == NULL)
		max = -1;
	else
		max = ltree->height;
	if (rtree != NULL)
		if (rtree->height > max)
			max = rtree->height;
	return max;		
}

struct node *delete_node(struct node *root, struct interval element) {   
	struct node *temp;
	if (root == NULL)
		return root;
	if (element.f < root->data.s)
		root->left = delete_node(root->left, element);
	else if (element.s > root->data.f)
		root->right = delete_node(root->right, element);
	else {
		if ((root->left == NULL) || (root->right == NULL)) {
			temp = root->left ? root->left : root->right;
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else {
			temp = root->right;
			while (temp->left != NULL) {
				temp = temp->left;
            }
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
		}
	}
	if (root == NULL)
    	return root;
    root->height = max_height(root->left, root->right) + 1;
    root = check_balance(root);
    return root;
}

int find_time(struct node *root, long *total, long K) {
    int rt, ret;
    if (root != NULL) {
    	ret = find_time(root->left, total, K);
    	if (ret)
    		return ret;
    	*total = *total + (root->data.f - root->data.s + 1) * root->data.flow;
    	if (*total >= K) {
    		*total = *total - (root->data.f - root->data.s + 1) * root->data.flow;
    		if (((K - (*total)) % root->data.flow)) 
    			rt = ((K - (*total)) / root->data.flow) + 1;
    		else 
    			rt = ((K - (*total)) / root->data.flow);
        	return root->data.s + rt - 1;
    	}
    	ret = find_time(root->right, total, K);
    	return ret;
    }
    return 0;
}

result parse() {
	int i, N;
	long K;
	long t = 0;
	struct interval element;
	struct node *intervals = NULL;
	result res;
	scanf("%d %ld", &N, &K);
	for (i = 0; i < N; i++) {
		scanf("%d %d", &element.s, &element.f);
		element.flow = 1;
		intervals = insert_node(intervals, element);
		t += count_nodes(intervals);
	}
	printf("%ld\n", t);
	res.intervals = intervals;
	res.K = K;
	return res;
}


int main(void) {
	long total = 0;
	result res;
	res = parse();
	printf("%d\n", find_time(res.intervals, &total, res.K));
	return 0;
}








