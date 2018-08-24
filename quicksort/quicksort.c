#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char *keys;
	long int N, i;

	FILE *file;

	if ((file = fopen("quicksort.in", "r")) == NULL) {
		perror("quicksort.in");
		exit(1);
	}

	fscanf(file, "%ld", &N);
	keys = (char*) malloc(N * 8);
	if (keys == NULL) {
		perror("Memory allocation");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < N; i++)
		fscanf(file, "%s", keys + (i * 8));
	fclose(file);

	qsort(keys, N, 8, (int(*)(const void *, const void *)) strcmp);

	if ((file = fopen("quicksort.out", "w")) == NULL) {
		perror("quicksort.out");
		exit(1);
	}

	for (i = 0; i < N; i++)
		fprintf(file, "%s\n", keys + (i * 8));

	fclose(file);
	free(keys);

	return EXIT_SUCCESS;
}
