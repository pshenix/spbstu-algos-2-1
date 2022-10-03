#pragma warning(disable : 4996)
#include <stdio.h>
#include "function.h"

int main()
{
	FILE* file_1 = fopen("spisok_1.txt", "r");
	sort(file_1);
	FILE* file_2 = fopen("spisok_2.txt", "r");
	sort(file_2);
}








