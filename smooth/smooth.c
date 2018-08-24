#include <stdio.h>
#include <stdlib.h>

#define image(x,y) pixels[x*width+y]
#define smooth(x,y) filtered[x*width+y]

int main(int argc, char *argv[]) {

	FILE *in;
	FILE *out;

	in = fopen("movie.in", "rb");
	if (in == NULL) {
		perror("movie.in");
		exit(EXIT_FAILURE);
	}

	out = fopen("movie.out", "wb");
	if (out == NULL) {
		perror("movie.out");
		exit(EXIT_FAILURE);
	}

	int width, height;

	fread(&width, sizeof(width), 1, in);
	fread(&height, sizeof(height), 1, in);

	fwrite(&width, sizeof(width), 1, out);
	fwrite(&height, sizeof(height), 1, out);

	int *pixels = (int *) malloc(height * width * sizeof(int));
	int *filtered = (int *) malloc(height * width * sizeof(int));

	int DY[] = { -1, -1, -1, +0, +0, +0, +1, +1, +1 };
	int DX[] = { -1, +0, +1, -1, +0, +1, -1, +0, +1 };
	int x, y, d, dx, dy;

	do {
		if (!fread(pixels, height * width * sizeof(int), 1, in))
			break;

		for (y = 0; y < height; y++) {
			for (x = 0; x < width; x++) {
				long long int sum = 0;
				for (d = 0; d < 9; d++) {
					dx = x + DX[d];
					dy = y + DY[d];
					if (dx >= 0 && dx < width && dy >= 0 && dy < height)
						sum += image(dy, dx);
				}
				smooth(y, x) = sum / 9;
			}
		}

		fwrite(filtered, height * width * sizeof(int), 1, out);
	} while (!feof(in));

	free(pixels);
	free(filtered);

	fclose(out);
	fclose(in);

	return EXIT_SUCCESS;
}
