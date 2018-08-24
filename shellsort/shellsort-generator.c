#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGTH 8
#define TAM (long int)10000000

int main(int argc, char *argv[]) {
	char str[LENGTH];
	long int tam;
	long int c;
	FILE *fout;

	srand(time(NULL));
	fout = fopen("shellsort.in", "w");
	if (fout == NULL) {
		perror("shellsort.in");
		exit(EXIT_FAILURE);
	}

	if (argc == 1)
		tam = TAM;
	else
		tam = atol(argv[1]);

	fprintf(fout, "%ld\n", tam);

	while (tam > 0) {
		for (c = 0; c < LENGTH-1; c++) {
			str[c] = 33 + (rand() % 94);
		}
		str[c] = 0;
		fprintf(fout, "%s\n", str);
		tam--;
	}

	fflush(fout);
	fclose(fout);

	return EXIT_SUCCESS;
}
