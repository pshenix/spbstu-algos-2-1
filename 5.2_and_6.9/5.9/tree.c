#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
# define N 5

typedef struct tree
{
	int value;
	struct tree* left;
	struct tree* right;

}tree;

tree* Binary_Tree(int node[N][N]){
	tree* nodes[N]; //create an array of nodes
	for (int i = 0; i < N; i++){
		nodes[i] = (tree*)malloc(sizeof(tree));
		nodes[i]->value = i;
		nodes[i]->left = NULL;
		nodes[i]->right = NULL;
	}
	tree* root = NULL;
	int parent;
	// for the child, we are looking for direct parents moving along the matrix to all other parents
	for (int j = 0; j < N; j++){
		parent = 0; // initially for the child in the j column there is no current parent
		for (int i = 0; i < N; i++){ // go through the rows of the matrix in search of the parent
			if (node[i][j] != 0){
				if (parent == 0) { parent = i; }//if the current parent has not yet been, then i number in the j column becomes it
				else {
					if (node[parent][i] == 1) { //if the old parent is not direct, then delete the relationship
						node[parent][j] = 0;
						parent = i;
					}
					else { node[i][j] = 0; }
					// if the old parent is direct, then the new one is the ancestor and break the relationship of that new one
				}
			}
		}
		//now the current parent is the j node's direct parent
		if (parent == 0){
			//if no ancestors were found for the node, then it is the root
			root = nodes[j];
		}
		else{
			//distribute to a free branch
			if ((nodes[parent]->left) == NULL) { nodes[parent]->left = nodes[j]; }
			else { nodes[parent]->right = nodes[j]; }
		}
	}
	return root;
}
//function that creates a binary tree

//function that print a binary tree, passing through the nodes

void TreePrint(tree* t, int level) {
	if (t) {
		TreePrint(t->right, level + 1);
		for (int i = 0; i < level; i++) { printf("		"); }
		printf("%d\n", t->value);
		TreePrint(t->left, level + 1);
	}
}

int main(){
	int matrix[N][N] = {
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 1, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 0 }, };
	tree* root = Binary_Tree(matrix);
	printf("Binary tree:\n");
	TreePrint(root, 0);
	printf("\n");
}