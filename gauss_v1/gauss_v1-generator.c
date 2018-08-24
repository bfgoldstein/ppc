#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * SIZE: 3700
 * TIME: 2m14s
 */

#define RAND rand() % 15

int next(int n) {
	if ((n & -n) == n)
		return (int) ((n * (long) next(31)) >> 31);

	int bits, val;
	do {
		bits = next(31);
		val = bits % n;
	} while (bits - val + (n - 1) < 0);
	return val;
}

long double nextLongDouble() {
	long long int v, o;
	v = (long long int) (next(26)) << 27;
	o = 1;
	return (v + next(27)) / (long double) (o << 53);
}

int main(void) {
	FILE *file;
	int i, j;
	int n = 3700;

	srand(time(NULL));

	if ((file = fopen("gauss.in", "w")) == NULL) {
		perror("File INPUT!");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "%d\n", n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (rand() % 7)
				fprintf(file, "%d ", RAND);
			else
				fprintf(file, "%d ", -RAND);
		}
		fprintf(file, "\n");
	}
	for (i = 0; i < n; i++)
		if (rand() % 10)
			fprintf(file, "%d ", RAND);
		else
			fprintf(file, "%d ", -RAND);
	fprintf(file, "\n");

	fflush(file);
	fclose(file);
	return EXIT_SUCCESS;
}
