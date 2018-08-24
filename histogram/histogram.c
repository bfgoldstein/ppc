#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RGB_COMPONENT_COLOR 255

typedef struct {
	unsigned char red, green, blue;
} PPMPixel;

typedef struct {
	int x, y;
	PPMPixel *data;
} PPMImage;

static PPMImage *readPPM() {
	char buff[16];
	PPMImage *img;
	FILE *fp;
	int c, rgb_comp_color;
  fp = stdin;

	if (!fgets(buff, sizeof(buff), fp)) {
		perror("stdin");
		exit(1);
	}

	if (buff[0] != 'P' || buff[1] != '6') {
		fprintf(stderr, "Invalid image format (must be 'P6')\n");
		exit(1);
	}

	img = (PPMImage *) malloc(sizeof(PPMImage));
	if (!img) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	c = getc(fp);
	while (c == '#') {
		while (getc(fp) != '\n')
			;
		c = getc(fp);
	}

	ungetc(c, fp);
	if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
		fprintf(stderr, "Invalid image size (error loading)\n");
		exit(1);
	}

	if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
		fprintf(stderr, "Invalid rgb component (error loading)\n");
		exit(1);
	}

	if (rgb_comp_color != RGB_COMPONENT_COLOR) {
		fprintf(stderr, "Image does not have 8-bits components\n");
		exit(1);
	}

	while (fgetc(fp) != '\n')
		;
	img->data = (PPMPixel*) malloc(img->x * img->y * sizeof(PPMPixel));

	if (!img) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
		fprintf(stderr, "Error loading image.\n");
		exit(1);
	}

	return img;
}


void Histogram(PPMImage *image, float *h) {

	int i, j,  k, l, x, count;
	int rows, cols;

	float n = image->y * image->x;

	cols = image->x;
	rows = image->y;

	for (i = 0; i < n; i++) {
		image->data[i].red = floor((image->data[i].red * 4) / 256);
		image->data[i].blue = floor((image->data[i].blue * 4) / 256);
		image->data[i].green = floor((image->data[i].green * 4) / 256);
	}

	count = 0;
	x = 0;
	for (j = 0; j <= 3; j++) {
		for (k = 0; k <= 3; k++) {
			for (l = 0; l <= 3; l++) {
				for (i = 0; i < n; i++) {
					if (image->data[i].red == j && image->data[i].green == k && image->data[i].blue == l) {
						count++;
					}
				}
				h[x] = count / n;
				count = 0;
				x++;
			}
		}
	}
}

int main(int argc, char *argv[]) {

	int i;

	PPMImage *image = readPPM();

	float *h = (float*)malloc(sizeof(float) * 64);

	for(i=0; i < 64; i++) h[i] = 0.0;

	Histogram(image, h);

	for (i = 0; i < 64; i++){
		printf("%0.3f ", h[i]);
	}
	printf("\n");
	free(h);

	return 0;
}
