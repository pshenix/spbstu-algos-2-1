#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#pragma warning(disable:4996)

int Min(int a, int b) {
	return (a > b ? a : b);
}

int*** CreateMap(char* f1, char* f2, int* n) {
	FILE* file_cost = fopen(f1, "r"), * file_time = fopen(f2, "r");
	if (file_cost == NULL || file_time == NULL) { printf("\nError during opening files."); return; }
	// counting towns in matrix
	char ch, p = EOF;
	int N = 0;
	while ((ch = fgetc(file_cost)) != EOF) { 
		p = ch; 
		if (ch == '\n') { N++; }
	}
	if (p != '\n') { N++; }
	fseek(file_cost, 0, SEEK_SET);
	*n = N;
	// filling array of towns with parameters (cost & time)
	int*** arr = (int***)malloc(N * sizeof(int**));
	for (int i = 0; i < N; i++) {
		arr[i] = (int**)malloc(N * sizeof(int*));
	}
	for (int i = 0; i < N; i++) {
		arr[i][i] = (int*)calloc(2, sizeof(int));
		int cost = 0, time = 0;
		for (int q = 0; q < i + 1; q++) { // scanning files with datas 
			fscanf(file_cost, "%d", &cost);
			fscanf(file_time, "%d", &time);
		}
		for (int j = i + 1; j < N; j++) {
			arr[i][j] = (int*)malloc(2 * sizeof(int));
			arr[j][i] = (int*)malloc(2 * sizeof(int));
			fscanf(file_cost, "%d", &cost);
			fscanf(file_time, "%d", &time);
			arr[i][j][0] = cost; arr[j][i][0] = cost;
			arr[i][j][1] = time; arr[j][i][1] = time;
		}
	}
	return arr;
}

void SalesMan(int*** matrix, int n, int* way, int count, int time, int* min_time, int money, int max_cost, int* towns, int* ans) {
	if (time >= *min_time || money > max_cost) {
		return;
	}
	if (count == n) {
		*min_time = min(time + matrix[way[count - 1]][0][0], *min_time);
		for (int i = 0; i < n; i++) {
			ans[i] = way[i];
		}
		return;
	}
	for (int i = 1; i < n; i++) {
		if (towns[i] != 1) {
			towns[i] = 1; way[count] = i;
			time += matrix[way[count - 1]][way[count]][0];
			money += matrix[way[count - 1]][way[count]][1];
			SalesMan(matrix, n, way, count + 1, time, &min_time, money, max_cost, towns, ans);
			towns[i] = 0;
		}
	}

}

int main() {
	int n; // number of towns
	int min_time = pow(10, 9); // default value to high broad for time
	int max_cost = 60; // max acceptable summ
	char* f1 = "cost.txt", * f2 = "time.txt";
	int*** map = CreateMap(f1, f2, &n);

	printf("For these condithions the way is\n");
	int* way = (int*)calloc(n, sizeof(int)); // transitory path
	int* ans = (int*)calloc(n, sizeof(int)); // final way
	ans[0] = -1; // default value for when cannot to find any solution to starting conditions 
	int* towns = (int*)calloc(n, sizeof(int));
	towns[0] = 1; // cause we are already here
	// parameters for recursion SalesMan:
	// 1)matrix of map, 2)count towns, 3)possible path, 4)count passed towns, 5)transitory time
	// 6)answer for time, 7)transitory sum of cost, 8)max_cost, 9)passed towns, 10)final way
	SalesMan(map, n, way, 1, 0, &min_time, 0, max_cost, towns, ans);
	if (ans[0] == -1) printf("It is not a lot of money for such a trip, buddy");
	else {
		for (int i = 0; i < n; i++) {
			printf("%d -> ", ans[i] + 1);
		}
		printf("1");
	}
	return 0;
}

