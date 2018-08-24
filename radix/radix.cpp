#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stack>

using namespace std;

FILE *fin, *fout;

char *keys;
long int N;

void openfiles() {
	fin = fopen("radix.in", "r+");
	if (fin == NULL) {
		perror("fopen fin");
		exit(EXIT_FAILURE);
	}

	fout = fopen("radix.out", "w");
	if (fout == NULL) {
		perror("fopen fout");
		exit(EXIT_FAILURE);
	}
}

void closefiles(void) {
	fclose(fin);
	fclose(fout);
}

typedef struct {
	long int s, e;
} job;

#define ascii 94
void radixsort(int s, int e, int b) {
	int hash[ascii];
	char key[8];
	long int i, j, x;
	int ss, ee;
	stack<job> stk;
	job quick;

	if (b > 7)
		return;

	memset(hash, 0, sizeof(int) * ascii);

	quick.s = s;
	quick.e = e;
	stk.push(quick);
	while (!stk.empty()) {
		quick = stk.top();
		stk.pop();
		ss = quick.s;
		ee = quick.e;

		i = ss + 1;
		j = ee;
		x = ee;
		while (i < j) {
			if (keys[i * 8 + b] < keys[ss * 8 + b])
				i++;
			else if (keys[i * 8 + b] > keys[ss * 8 + b]) {
				j--;
				x--;
				strcpy(key, keys + (i * 8));
				strcpy(keys + (i * 8), keys + (j * 8));
				strcpy(keys + (j * 8), keys + (x * 8));
				strcpy(keys + (x * 8), key);
			} else {
				j--;
				strcpy(key, keys + (i * 8));
				strcpy(keys + (i * 8), keys + (j * 8));
				strcpy(keys + (j * 8), key);
			}
		}
		i--;
		strcpy(key, keys + (i * 8));
		strcpy(keys + (i * 8), keys + (ss * 8));
		strcpy(keys + (ss * 8), key);

		if (i - ss > 1) {
			quick.s = ss;
			quick.e = i;
			stk.push(quick);
		}
		if (ee - x > 1) {
			quick.s = x;
			quick.e = ee;
			stk.push(quick);
		}
	}

	for (i = s; i < e; i++)
		hash[keys[i * 8 + b] - 33]++;

	for (i = 0, x = 0; i < ascii; i++) {
		if (hash[i] > 1)
			radixsort(s + x, s + x + hash[i], b + 1);

		x += hash[i];
	}
}

int main(int argc, char*argv[]) {

	long int i;

	openfiles();

	fscanf(fin, "%ld", &N);
	keys = (char*) malloc(N * 8);
	if (keys == NULL) {
		perror("malloc keys");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < N; i++)
		fscanf(fin, "%s", keys + (i * 8));

	radixsort(0, N, 0);

	for (i = 0; i < N; i++)
		fprintf(fout, "%s\n", keys + (i * 8));

	free(keys);
	closefiles();
	return EXIT_SUCCESS;
}
