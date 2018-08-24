#include <stdio.h>
#include <stdlib.h>
#include "bucketsort.h"

#define LENGTH 8

FILE *fin, *fout;

char *strings;
long int N;

void openfiles() {
	fin = fopen("bucketsort.in", "r+");
	if (fin == NULL) {
		perror("fopen fin");
		exit(EXIT_FAILURE);
	}

	fout = fopen("bucketsort.out", "w");
	if (fout == NULL) {
		perror("fopen fout");
		exit(EXIT_FAILURE);
	}
}

void closefiles(void) {
	fclose(fin);
	fclose(fout);
}

int main(int argc, char* argv[]) {

	long int i, *r;

	openfiles();

	fscanf(fin, "%ld", &N);
	strings = (char*) malloc(N * LENGTH);
	if (strings == NULL) {
		perror("malloc strings");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < N; i++)
		fscanf(fin, "%s", strings + (i * LENGTH));

	fflush(stdout);

	r = bucket_sort(strings, LENGTH, N);

	fflush(stdout);

	for (i = 0; i < N; i++)
		fprintf(fout, "%s\n", strings + (r[i] * LENGTH));

	free(r);
	free(strings);
	closefiles();

	return EXIT_SUCCESS;
}
