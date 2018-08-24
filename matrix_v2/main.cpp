#include <iostream>
#include <fstream>
#include "matrix.h"

using namespace std;

int main() {

	int rows, columns;
	int i, j, value;

	ifstream in ("matrix.in");

	in >> rows >> columns;
	matrix A(rows, columns);
	for (i = 0; i < rows; i++)
		for (j = 0; j < columns; j++) {
			in >> value;
			A.set(i, j, value);
		}

	in >> rows >> columns;
	matrix B(rows, columns);
	for (i = 0; i < rows; i++)
		for (j = 0; j < columns; j++) {
			in >> value;
			B.set(i, j, value);
		}

	in.close();

	A = A * B;

	ofstream out("matrix.out");
	out << A;
	out.close();

	return 0;
}
