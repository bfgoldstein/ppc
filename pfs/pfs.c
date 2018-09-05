#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// #define DEBUG

typedef struct {
	int i[21];
	int exec[21];
	int maq;
} task;
int n, m;
task tasks[101];
int machines[21];

int main(int argc, char* argv[]) {

	int i, j;
	FILE *in, *out;
	int makespan, min_makespan;
	int seq[101];
	int cont_n;

	in = fopen("pfs.in", "r");
	out = fopen("pfs.out", "w");

	while (1) {
		memset(tasks, 0, sizeof(tasks));

		fscanf(in, "%d%d", &n, &m);
		if (n == 0 || m == 0)
			break;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++)
				fscanf(in, "%d", &tasks[i].i[j]);
		}
		min_makespan = 0;

		// generate first sequence
		for (i = 0; i < n; i++)
			seq[i] = i;

		do {
			for (i = 0; i < m; i++)
				machines[i] = -1;
			makespan = 0;
			for (i = 0; i < n; i++) {
				memset(tasks[i].exec, 0, sizeof(tasks[i].exec));
				tasks[i].maq = 0;
			}

			cont_n = 0;

			// simulate permutation flow job schedule
			while (cont_n < n) {

				// schedule each task on a machine
				for (i = cont_n; i < n; i++) {
					if (machines[tasks[seq[i]].maq] < 0) {
						machines[tasks[seq[i]].maq] = seq[i];
					}
				}

				//run task
				for (i = 0; i < m; i++) {
					if (machines[i] >= 0) {
						tasks[machines[i]].exec[i]++;
						if (tasks[machines[i]].exec[i]
								>= tasks[machines[i]].i[i]) {
							// free a machine
							tasks[machines[i]].maq++;
							if (tasks[machines[i]].maq >= m)
								cont_n++;
							machines[i] = -1;
						}
					}
				}
				makespan++;
			}

			// calculate makespan
			if (!min_makespan || makespan < min_makespan)
				min_makespan = makespan;

			// generate another sequence
			cont_n = 1;
			while (cont_n) {
				i = n - 1;
				seq[i]++;
				while (seq[i] >= n) {
					for (j = i; j < n; j++)
						seq[j] = 0;
					if ((i - 1) >= 0)
						seq[--i]++;
				}
				cont_n = 0;
				for (i = 0; i < n && !cont_n; i++)
					for (j = i + 1; j < n && !cont_n; j++)
						if (seq[i] == seq[j])
							cont_n = 1;
			}
			cont_n = 1;
			for (i = 0; i < n - 1 && cont_n; i++)
				if (seq[i] > seq[i + 1])
					cont_n = 0;
			if (cont_n)
				break;

#ifdef DEBUG
			for (i = 0; i < n; i++)
				printf("%d ", seq[i]);
			printf("\n");
			fflush(stdout);
#endif

		} while (1);

		fprintf(out, "%d\n", min_makespan);
		fflush(out);
	}

	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}
