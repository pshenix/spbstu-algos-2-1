#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include <stdio.h>
#pragma warning(disable:4996)
#define N 100

typedef struct list {
	double value;
	struct list* next;
} list;

list* Create_list(double val) {
	list* tmp = (list*)malloc(sizeof(list));
	tmp->value = val;
	tmp->next = NULL;
	return(tmp);
}

list* Add_elem_start(double val, list* head) {
	list* tmp = (list*)malloc(sizeof(list));
	tmp->value = val;
	tmp->next = head;
	return tmp;
}

void Add_elem_end(double val, list* head) {
	list* tmp = (list*)malloc(sizeof(list));
	tmp->value = val;
	tmp->next = NULL;
	list* p = head;
	while (p->next != NULL) { p = p->next; }
	p->next = tmp;
}

list** Fill(char* filename, int* weidht, int* height) {
	list** arr = (list**)malloc(*height * sizeof(list*));
	FILE* f = fopen(filename, "r");
	if (f == NULL) { printf("\nError during opening file."); }
	else {
		int i = 0, j = 0, count = 0;

		/* counting strings of matrix */
		char ch, p = EOF;
		while ((ch = fgetc(f)) != EOF) {
			p = ch;
			if (ch == '\n') { i++; }
		}
		if (p != "\n") { i++; }
		fseek(f, 0, SEEK_SET);

		/* counting values */
		double c;
		while (fscanf(f, "%lf", &c) == 1) { count++; }
		j = (int)count / i;
		if (i * j != count) { printf("\nIncorrect notice of matrix."); }

		/* Filling massive of lists */
		else {
			arr = (list**)realloc(arr, sizeof(list*) * count);
			fseek(f, 0, SEEK_SET);
			*height = i; *weidht = j;
			for (int x = 0; x < i; x++) {
				fscanf(f, "%lf", &c);
				list* tmp = Create_list(c);
				for (int y = 1; y < j; y++) {
					fscanf(f, "%lf", &c);
					Add_elem_end(c, tmp);
				}
				arr[x] = tmp;
			}
		}
	}
	return arr;
}

list** Sum_matrix(list** arr1, list** arr2, int weidht, int height) {
	list** res = (list**)malloc(sizeof(list*) * weidht * height);
	for (int i = 0; i < height; i++) {
		list* l1 = arr1[i], * l2 = arr2[i];
		list* tmp = Create_list(l1->value + l2->value);
		for (int j = 1; j < weidht; j++) {
			l1 = l1->next; l2 = l2->next;
			Add_elem_end(l1->value + l2->value, tmp);
		}
		res[i] = tmp;
	}
	return res;
}

void Print_matrix(list** arr, int weidht, int height) {
	for (int i = 0; i < height; i++) {
		list* elem = arr[i];
		for (int j = 0; j < weidht; j++) {
			printf("%.3lf ", elem->value);
			elem = elem->next;
		}
		printf("\n");
	}
}

int main() {
	int height_1 = 0, weidht_1 = 0, height_2 = 0, weidht_2 = 0;

	list** arr_1 = Fill("matrix_1.txt", &weidht_1, &height_1);
	list** arr_2 = Fill("matrix_2.txt", &weidht_2, &height_2);
	if (height_1 == height_2 && weidht_1 == weidht_2) {
		list ** arr_res = Sum_matrix(arr_1, arr_2, weidht_1, height_1);
		Print_matrix(arr_res, weidht_1, height_1);
	}
	else { printf("\nError: different sizes of matrixes."); }
	/*
	Fill(arr_2, "matrix_2.txt", weidht_2, height_2);
	*/
	return 0;
}
