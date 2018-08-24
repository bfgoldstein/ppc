#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

	int N, i, j;
	int **M;
	FILE *out;

	srand(time(NULL));
	N = rand() % 2048 + 1024;

	out = fopen("mst.in", "w");

	M = calloc(N, sizeof(int*));
	for (i = 0; i < N; i++)
		M[i] = (int*) calloc(N, sizeof(int));

	for (i = 0; i < N; i++) {
		for (j = i + 1; j < N; j++) {
			if (rand() % 4 < 2) {
				M[i][j] = rand() % 65535;
				M[j][i] = M[i][j];
			}
		}
	}

	fprintf(out, "%d\n", N);
	fflush(out);
	printf("TOTAL: %d\n", N);
	fflush(stdout);
	for (i = 0; i < N; i++) {
		if (i % 1000 == 0) {
			printf("Vertice: %d\n", i);
			fflush(stdout);
		}
		for (j = 0; j < N; j++)
			fprintf(out, "%d ", M[i][j]);
		fprintf(out, "\n");
	}
	fflush(out);

	for (i = 0; i < N; i++)
		free(M[i]);
	free(M);

	fclose(out);

	return EXIT_SUCCESS;
}

