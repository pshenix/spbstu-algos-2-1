#pragma warning(disable : 4996)
#include <stdio.h>
#include <malloc.h>
#include "function.h"
#define WORD_LENGTH 32

list* create_node(char* word, int number)
{
	list* node = (list*)malloc(sizeof(list));
	node->word = word;
	node->number = number;
	node->next = NULL;
	return node;

}

list* NodeFile(FILE* file, char* format)
{
	int number;
	char* word = malloc(WORD_LENGTH * sizeof(char));

	if (fscanf(file, format, word, &number) != EOF)
		return create_node(word, number);

	return NULL;
}

list* insert(list* list_1, list* list_2)
{
	int flag = 0;
	list* sup = list_1;
	if (list_2->number < sup->number)
	{
		list_2->next = sup;
		return list_2;
	}
	while (sup != NULL)
	{
		if (sup->next == NULL)
		{
			sup->next = list_2;
			break;
		}
		else
		{
			if (list_2->number < sup->next->number) {
				list_2->next = sup->next;
				sup->next = list_2;
				break;
			}
			else if (list_2->number == sup->next->number)
			{
				list_2->next = sup->next;
				sup->next = list_2;
				break;
			}
			sup = sup->next;
		}
	}
	return list_1;
}

list* ListFile(FILE* file)
{
	list* head = NULL;
	list* cur = NULL;
	char* format = "%s %d";
	head = NodeFile(file, format);
	cur = NodeFile(file, format);
	while (cur != NULL) 
	{
		head = insert(head, cur);
		cur = NodeFile(file, format);
	}
	return head;
}

void print(list* head)
{
	printf("\n");
	for (list* node = head; node != NULL; node = node->next)
	{
		printf("%s %d\n", node->word, node->number);
	}
}

void Checknumber(list* head, int num)
{
	while (head != NULL)
	{
		if (head->number == num)
		{
			printf("\nYes.This words: %s\n", head->word);
		}
		head = head->next;
	}
}

void CheckRep(list* head)
{
	int flag = 0;
	list* cur = head;
	list* sup = head->next;
	while (cur != NULL)
	{
		sup = cur->next;
		while (sup!=NULL)
		{
			if (cur->number == sup->number)
				flag++;
			sup = sup->next;
		}
		cur = cur->next;
	}
	if (flag>0)
		printf("\nERROR\n");
}

void sort(FILE* file)
{
	int num = 0;
	list* list_1 = ListFile(file);
	print(list_1);
	CheckRep(list_1);
	scanf("%d", &num);
	Checknumber(list_1, num);
	free(list_1);
	fclose(file);
}
