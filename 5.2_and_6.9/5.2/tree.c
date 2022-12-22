#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#pragma warning(disable:4996)

typedef struct tree {
	int value, num;
	struct tree* left;
	struct tree* right;
}tree;

int** Fill(char const* filename) {
	FILE* f = fopen(filename, "r");
	int n; // value of nodes
	int num_kid, kid; // count of descendants and kids also 
	fscanf(f, "%d", &n);
	int** nodes = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &num_kid);
		nodes[i] = (int)malloc(sizeof(int) * num_kid);
		for(int j = 0; j < num_kid; j++){
			fscanf(f, "%d", &kid);
			nodes[i][j] = kid;
		}
	}
	fclose(f);
	return nodes;
}

tree* BuildingTree(tree* t, int** nodes, int num_node) {
	if(sizeof(nodes[num_node]) / sizeof(int*) == 1){
		t->left = BuildingTree(t, nodes, nodes[num_node][0]);
		t->right = NULL;
	}
	if (sizeof(nodes[num_node]) / sizeof(int*) == 2) {
		t->left = BuildingTree(t, nodes, nodes[num_node][0]);
		t->right = BuildingTree(t, nodes, nodes[num_node][1]);
	}
	if (sizeof(nodes[num_node]) == 0) {
		t->right = NULL; t->left = NULL;
	}
	return t;
}

int tree_petals(tree* t) {
	if (t->left != NULL) { t->value += tree_petals(t->left); }
	if (t->right != NULL) { t->value += tree_petals(t->right); }
	if (t->left == NULL && t->right == NULL) { return 1; }
	if (t->num == 0) { return 0; }
	else { return t->value; }
}

void TreePrint(tree* t, int level) {
	if (t) {
		TreePrint(t->left, level + 1);
		for (int i = 0; i < level; i++) { printf(" "); }
		printf("%d\n", t->value);
		TreePrint(t->right, level + 1);
	}
}

int main() {
	char const* filename = "tree.txt";
	int** nodes = Fill(filename);
	tree* t = malloc(sizeof(tree)); 
	t->value = 0; 
	t->num = 0; 
	t->left = NULL; 
	t->right = NULL;
	t = BuildingTree(t, nodes, 0);
	tree_petals(t);
	TreePrint(t, 0);
	return 0;
}