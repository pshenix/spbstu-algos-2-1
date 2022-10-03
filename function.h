#pragma once
typedef struct list
{
	char* word;
	int number;
	struct list* next;
}list;
list* create_node(char* word, int number);
list* NodeFile(FILE* file, char* format);
list* insert(list* list_1, list* list_2);
list* ListFile(FILE* file);
void print(list* head);
void CheckRep(list* head);
void Checknumber(list* head, int num);
void sort(FILE* file);
