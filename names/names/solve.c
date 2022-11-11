#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include <stdio.h>
#pragma warning(disable:4996)
#define N 50

struct Fio {
	char first_name[N];
	char middle_name[N];
	char last_name[N];
};

struct Fio* ReadText_v3(char const* filename, int* length) {
	FILE* f = fopen(filename, "r");
	int len = 1;
	struct Fio* names = (struct Fio*)malloc(len * sizeof(struct Fio));
	while (fscanf(f, "%s %s %s", names[len - 1].last_name, names[len - 1].first_name, names[len - 1].middle_name) == 3) {
		names = (struct Fio*)realloc(names, sizeof(struct Fio) * (++len));
	}
	fclose(f);
	*length = len - 1;
	return names;
}

void Sort(struct Fio* names, int len) {
	int count = 0;
	for (int i = 0; i < len; i++) {
		count = 0;
		for (int j = 0; j < len - i - 1; j++) {
			/* сравнение соседних строк */
			int flag = strcmp(names[j].last_name, names[j + 1].last_name);
			/* в случае, когда первая строка больше, мы меняем первую со второй местами */
			if (flag == 1) {
				char ln[N], fn[N], mn[N];
				strcpy(ln, names[j].last_name);
				strcpy(fn, names[j].first_name);
				strcpy(mn, names[j].middle_name);

				strcpy(names[j].last_name, names[j + 1].last_name);
				strcpy(names[j].first_name, names[j + 1].first_name);
				strcpy(names[j].middle_name, names[j + 1].middle_name);

				strcpy(names[j + 1].last_name, ln);
				strcpy(names[j + 1].first_name, fn);
				strcpy(names[j + 1].middle_name, mn);
				count++;
			}
		}
		/* не происходят перестановки, делаем выход из сортировки */
		if (count == 0) {
			break;
		}
	}
}

void Research(struct Fio* names, int len, char ln[], char fn[], char mn[]) {
	int count = 0, extra = (ln == NULL && fn == NULL && mn == NULL);
	for (int i = 0; i < len; i++) {
		int flag = 1, check = 1;
		if (ln != NULL) {
			for (int j = 0; j < strlen(ln); j++) {
				if (names[i].last_name[j] != ln[j]) { flag = 0; check = 0; break; }
			}
		}
		if (flag && fn != NULL) {
			for (int j = 0; j < strlen(fn); j++) {
				if (names[i].first_name[j] != fn[j]) { flag = 0; break; }
			}
		}
		if (flag && mn != NULL) {
			for (int j = 0; j < strlen(mn); j++) {
				if (names[i].middle_name[j] != mn[j]) { flag = 0; break; }
			}
		}
		if (flag == 1 || extra == 1) { count++; printf("%s %s %s\n", names[i].last_name, names[i].first_name, names[i].middle_name); }
		if (check == 0 && count > 0) { break; }
	}
	if (count == 0) { printf("Не найдены ФИО с заданными параметрами."); }
}

int main(void) {
	setlocale(LC_ALL, "Rus");

	char const *filename = "names.txt";
	int len = 0;
	struct Fio* names = ReadText_v3(filename, &len);
	Sort(names, len);

	char* first_name;
	char* middle_name;
	char* last_name;
	printf("Введите первые буквы для фио в виде: «буквы фамилии» «буквы имени» «буквы отчества»\n");
	char str[150];
	gets(str);
	while (strlen(str) != 0) {
		last_name = strtok(str, ">");
		first_name = strtok(NULL, " <");
		middle_name = strtok(NULL, "> <");
		first_name = strtok(first_name, "<>");
		last_name = strtok(last_name, "<");

		printf("\nРезультат поиска:\n");
		Research(names, len, last_name, first_name, middle_name);
		printf("\nЧтобы продолжить, введите первые буквы для фио в виде: «буквы фамилии» «буквы имени» «буквы отчества»\nДля окончание работы программы введите пустую строку\n");
		gets(str);
		printf("%s\n", str);
	}
	return 0;
}