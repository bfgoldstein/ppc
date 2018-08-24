#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#define ABS(n) ((n)>0?(n):-(n))

//#define DEBUG

long int N, K;
char *vars;
char satisfied = 0;
typedef struct {
	long int x1, x2, x3;
	char status;
} clause;
clause *formula;

int getAssignment(char *brute) {

	long int i = N;
	brute[i] += 1;
	while (brute[i] > 1 && i > 0) {
		brute[i] = 0;
		i--;
		brute[i] += 1;
	}
	if (i <= 0)
		return 0;
	return 1;
}

int brute() {

	char *brute = (char*) malloc(N + 1);
	memset(brute, 0, N + 1);
	long int i;

	i = 1;

	int found = 0;
	char v;

	while (!found && !satisfied) {
		if (!getAssignment(brute)) {
			found = 0;
			break;
		}
		v = 1;
		for (i = 0; v && i < K; i++) {
			v = 0;
			if (formula[i].x1 > 0)
				v = v | brute[formula[i].x1];
			else
				v = v | !brute[-formula[i].x1];
			if (formula[i].x2 > 0)
				v = v | brute[formula[i].x2];
			else
				v = v | !brute[-formula[i].x2];
			if (formula[i].x3 > 0)
				v = v | brute[formula[i].x3];
			else
				v = v | !brute[-formula[i].x3];
		}
		found = v;
	}

	if (found) {
		if (!satisfied) {
			memcpy(vars, brute, N + 1);
		}
		satisfied = 1;
	}

	free(brute);
	return satisfied;
}

void _3sat() {
	brute();
}

int main(int argc, char *argv[]) {

	long int i;

	scanf("%ld %ld", &N, &K);
	vars = (char*) malloc(N + 1);
	memset(vars, 0, N + 1);
	formula = (clause *) calloc(K, sizeof(clause));
	if (vars == NULL || formula == NULL) {
		fprintf(stderr, "malloc/calloc\n");
		fflush(stderr);
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < K; i++) {
		scanf("%ld %ld %ld", &formula[i].x1, &formula[i].x2, &formula[i].x3);
		formula[i].status = 1;
	}

	_3sat();

	if (satisfied) {
		for (i = 1; i <= N; i++)
			printf("%ld %c\n", i, vars[i] == 1 ? 'T' : 'F');
		fflush(stdout);
	} else {
		printf("Solution is not possible\n");
		fflush(stdout);
	}

	free(vars);
	free(formula);
	return EXIT_SUCCESS;
}

