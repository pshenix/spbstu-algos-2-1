#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include <stdio.h>
#pragma warning(disable:4996)

typedef struct tree {
	int num, key;
	struct tree* left, * right;
} tree;

void TreePrint(tree* t, int lvl) {
	if (t) {
		TreePrint(t->left, lvl + 1);
		for (int i = 0; i < lvl; i++) { printf("      "); }
		printf("%d", t->key);
		TreePrint(t->right, lvl + 1);
		printf("\n");
	}
}

int Counting(tree* t) {
	if (t->left != NULL) { t->num += Counting(t->left); }
	if (t->right != NULL) { t->num += Counting(t->right); }
	if (t->left == NULL && t->right == NULL) { return 1; }
	return t->num;
}

void Search_k(tree* t, int k, int* flag) {
	int r;
	if (t->left) { r = t->left->num + 1; }
	else { r = 1; }
	if (r != k) {
		if (k < r) { Search_k(t->left, k, flag); }
		else { Search_k(t->right, k - r, flag); }
	}
	else {
		if (t->key % 2 == 0) { *flag = 1; }
		printf("k min element %d\n", t->key);
	}
}

void SmallerElemThanK(tree* t, int k, int elem) {
	int min = 1 + elem;
	if (t->left) {
		SmallerElemThanK(t->left, k, 0);
		min += t->left->num;
	}
	if (min <= k) {
		printf("\n%d min elem: %d\n", min, t->key);
		if (t->right) { SmallerElemThanK(t->right, k, min); }
	}
}

tree* newNode(int node_key) {
	tree* node; node = malloc(sizeof(tree));
	node->key = node_key;
	node->num = 1;
	node->left = NULL; node->right = NULL;
	return node;
}

tree* add(tree* t, int node_key) {
	if (!t) { return newNode(node_key); }
	if (node_key < t->key) { t->left = add(t->left, node_key); }
	if (node_key > t->key) { t->right = add(t->right, node_key); }
	return t;
}

int main() {
	tree* t = NULL; // create tree
	int n, node_key, k;
	printf("Write count of tree's nodes: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("\nEnter %d value of node: ", i + 1);
		scanf("%d", &node_key);
		t = add(t, node_key);
	}
	// found value of number in each node
	Counting(t);
	// create flag and call function to find k-th min elem
	// if min elem % 2 == 0 -> flag = 1 else flag = 0
	int flag = 0;
	printf("\nWrite value of k: ");
	scanf("%d", &k);
	Search_k(t, k, &flag);
	if (flag == 1) {
		SmallerElemThanK(t, k, 0);
	}
	printf("\nFinal tree: \n");
	TreePrint(t, 0);
	return 0;
}