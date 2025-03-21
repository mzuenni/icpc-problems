/**
 * Author: Thomas Beuman
 *
 * Time: O((n+q) log n)
 *   (log n for every level that is filled, plus log n for the rest of every query)
 */

#include <algorithm>
#include <cstdio>
using namespace std;

const int NMAX = 300000;

struct Node {
	Node* left, *right, *parent;
	int lb, ub, mid;
	bool isleaf;
	int capacity, amount;
	int max_capacity; // Maximum capacity of all levels under this node
	int max_unfilled; // Capacity of largest not-full level
	                  // (not shielded by larger level under this node)
	Node() {
		parent = NULL;
	}
};

int Capacity[NMAX];
Node* root;

Node* build_tree (int lb, int ub)
{
	Node* node = new Node();
	node->lb = lb;
	node->ub = ub;
	if (ub - lb == 1) {
		node->isleaf = true;
		int i = lb;
		node->capacity = Capacity[i];
		node->amount = 0;
		node->max_capacity = Capacity[i];
		node->max_unfilled = Capacity[i];
	}
	else {
		node->isleaf = false;
		int mid = (lb+ub)/2;
		node->mid = mid;
		node->left = build_tree(lb, mid);
		node->right = build_tree(mid, ub);
		node->left->parent = node;
		node->right->parent = node;
		node->max_capacity = max(node->left->max_capacity, node->right->max_capacity);
		node->max_unfilled = node->max_capacity;
	}
	return node;
}

Node* getleaf (int i)
{
	Node* node = root;
	while (!node->isleaf)
		node = (i < node->mid ? node->left : node->right);
	return node;
}

void update_unfilled (Node* node)
{
	node = node->parent;
	while (node) {
		if (node->right->max_unfilled > node->left->max_capacity)
			node->max_unfilled = node->right->max_unfilled;
		else
			node->max_unfilled = node->left->max_unfilled;
		node = node->parent;
	}
}

// Find the next level that will collect overflow
Node* getnext (Node* node)
{
	int capacity = node->capacity;
	// First, back up the tree until we can "turn right"
	while (node != root) {
		bool isLeftChild = (node == node->parent->left);
		node = node->parent;
		if (isLeftChild) {
			if (node->right->max_unfilled > capacity) {
				node = node->right;
				// Next level is in this subtree
				break;
			}
			capacity = max(capacity, node->right->max_capacity);
		}
	}
	if (node == root) // Spill over
		return NULL;
	// Second, down the tree toward first unfilled level above capacity
	while (!node->isleaf) {
		if (node->left->max_unfilled > capacity)
			node = node->left;
		else {
			capacity = max(capacity, node->left->max_capacity);
			node = node->right;
		}
	}
	return node;
}

void delete_tree (Node* node)
{
	if (!node->isleaf) {
		delete_tree(node->left);
		delete_tree(node->right);
	}
	delete node;
}

int main()
{
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 0; i < n; i++)
		scanf("%d ", &Capacity[i]);

	root = build_tree(0, n);
	for (int j = 0; j < q; j++) {
		char t;
		scanf("%c", &t);
		if (t == '+') {
			int i, x;
			scanf("%d %d ", &i, &x);
			i--;
			Node* node = getleaf(i);
			while (node && node->amount + x >= node->capacity) {
				// Fill up level and go to next level
				x -= node->capacity - node->amount;
				node->amount = node->capacity;
				node->max_unfilled = 0;
				update_unfilled(node);
				node = getnext(node);
			}
			if (node)
				node->amount += x;
		}
		else {
			int i;
			scanf("%d ", &i);
			i--;
			Node* node = getleaf(i);
			printf("%d\n", node->amount);
		}
	}
	delete_tree(root);
	return 0;
}
