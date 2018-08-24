#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Solves the 3-SAT system using an exaustive search
// It finds all the possible values for the set of variables using
// a number. The binary representation of this number represents 
// the values of the variables. Since a long variable has 64 bits, 
// this implementations works with problems with up to 64 variables.
long solveClauses(short **clauses, int nClauses, int nVar) {

	long *iVar = (long *) malloc(nVar * sizeof(long));
	int i;
	for (i = 0; i < nVar; i++)
		iVar[i] = exp2(i);

	unsigned long maxNumber = exp2(nVar);
	long number;
	short var;
	int c;

	for (number = 0; number < maxNumber; number++) {

		for (c = 0; c < nClauses; c++) {

			var = clauses[0][c];
			if (var > 0 && (number & iVar[var - 1]) > 0)
				continue; // clause is true
			else if (var < 0 && (number & iVar[-var - 1]) == 0)
				continue; // clause is true

			var = clauses[1][c];
			if (var > 0 && (number & iVar[var - 1]) > 0)
				continue; // clause is true
			else if (var < 0 && (number & iVar[-var - 1]) == 0)
				continue; // clause is true

			var = clauses[2][c];
			if (var > 0 && (number & iVar[var - 1]) > 0)
				continue; // clause is true
			else if (var < 0 && (number & iVar[-var - 1]) == 0)
				continue; // clause is true

			break; // clause is false
		}

		if (c == nClauses)
			return number;

	}
	return -1;

}

// Read nClauses clauses of size 3. nVar represents the number of variables
// Clause[0][i], Clause[1][i] and Clause[2][i] contains the 3 elements of the i-esime clause.
// Each element of the caluse vector may contain values selected from:
// k = -nVar, ..., -2, -1, 1, 2, ..., nVar. The value of k represents the index of the variable.
// A negative value remains the negation of the variable.
short **readClauses(int nClauses, int nVar) {

	short **clauses = (short **) malloc(3 * sizeof(short *));
	clauses[0] = (short *) malloc(nClauses * sizeof(short));
	clauses[1] = (short *) malloc(nClauses * sizeof(short));
	clauses[2] = (short *) malloc(nClauses * sizeof(short));

	int i;
	for (i = 0; i < nClauses; i++) {
		scanf("%hd %hd %hd", &clauses[0][i], &clauses[1][i], &clauses[2][i]);
	}

	return clauses;
}

int main(int argc, char *argv[]) {

	int nClauses;
	int nVar;

	scanf("%d %d", &nClauses, &nVar);

	short **clauses = readClauses(nClauses, nVar);

	long solution = solveClauses(clauses, nClauses, nVar);

	int i;
	if (solution >= 0) {
		printf("Solution found [%ld]: ", solution);
		for (i = 0; i < nVar; i++)
			printf("%d ", (int) ((solution & (long) exp2(i)) / exp2(i)));
		printf("\n");
	} else
		printf("Solution not found.\n");

	return EXIT_SUCCESS;
}

