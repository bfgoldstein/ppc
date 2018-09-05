#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void prim(float **W, int **T, int N) {
	int i, j, k = 0;
	int *nearNode = (int*) calloc(N, sizeof(int));
	float *minDist = (float*) calloc(N, sizeof(float));
	float min;

	for (i = 1; i < N; i++) {
		nearNode[i] = 0;
		minDist[i] = W[i][0];
	}
	for (i = 0; i < N - 1; i++) {
		min = FLT_MAX;
		for (j = 1; j < N; j++) {
			if (0 <= minDist[j] && minDist[j] < min) {
				min = minDist[j];
				k = j;
			}
		}
		T[i][0] = nearNode[k];
		T[i][1] = k;
		minDist[k] = -1;
		for (j = 1; j < N; j++) {
			if (W[j][k] < minDist[j]) {
				minDist[j] = W[j][k];
				nearNode[j] = k;
			}
		}
	}
	free(nearNode);
	free(minDist);
}

int main(int argc, char *argv[]) {

	FILE *in, *out;
	int N;
	float **M;
	int **T;
	int i, j, k, f;

	in = fopen("mst.in", "r");
	out = fopen("mst.out", "w");

	fscanf(in, "%d", &N);
	M = calloc(N, sizeof(float*));
	for (i = 0; i < N; i++) {
		M[i] = calloc(N, sizeof(float));
		for (j = 0; j < N; j++) {
			fscanf(in, "%f", &M[i][j]);
			if (M[i][j] == 0)
				M[i][j] = FLT_MAX;
		}
	}
	T = calloc(N, sizeof(int*));
	for (i = 0; i < N; i++) {
		T[i] = calloc(2, sizeof(int));
	}

	prim(M, T, N);

	for (i = 0; i < N; i++) {
		f = 0;
		for (j = 0; j < N; j++) {
			for (k = 0; k < N - 1; k++) {
				if (T[k][0] == i && T[k][1] == j) {
					if (f == 0) {
						fprintf(out, "%d -> %d", T[k][0], T[k][1]);
						f++;
					} else
						fprintf(out, ",%d", T[k][1]);
				}
			}
		}
		if (f)
			fprintf(out, "\n");
	}
	fflush(out);

	for (i = 0; i < N; i++) {
		free(M[i]);
		free(T[i]);
	}
	free(M);
	free(T);
	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}
