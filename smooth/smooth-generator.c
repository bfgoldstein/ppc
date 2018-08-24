#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * SIZE: 1700 1250
 * TIME: +/-20 min
 *
 */

#define image(x,y) pixels[x*width+y]

int main(void) {
	srand(time(NULL));
	int width, heigth;
	int x, y, i, max;

	FILE *out;

	out = fopen("movie.in", "wb");
	if (out == NULL) {
		perror("movie.out");
		exit(EXIT_FAILURE);
	}

	width = rand() % 512 + 1536;
	heigth = rand() % 384 + 1152;

	fwrite(&width, sizeof(width), 1, out);
	fwrite(&heigth, sizeof(heigth), 1, out);
	fflush(out);

	int *pixels = (int*) malloc(heigth * width * sizeof(int));

	max = 4000;
	for (i = 0; i < max; i++) {
		for (y = 0; y < heigth; y++) {
			for (x = 0; x < width; x++) {
				image(y,x) = rand();
			}
		}
		fwrite(pixels, heigth * width * sizeof(int), 1, out);
	}

	free(pixels);
	fflush(out);
	fclose(out);

	return EXIT_SUCCESS;
}
