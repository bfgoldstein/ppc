#include "matrix.h"

matrix::matrix(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;
	m = new int[rows * columns];
}

matrix::~matrix() {
	delete m;
	m = NULL;
}

matrix& matrix::operator*(matrix& B) {
	matrix A = (*this);
	if (A.columns != B.rows)
		throw A.columns != B.rows;
	int *m = new int[A.rows * B.columns];
	int i, j, k, c;

	for (i = 0; i < A.rows; i++)
		for (j = 0; j < B.columns; j++) {
			c = i * B.columns + j;
			m[c] = 0;
			for (k = 0; k < A.columns; k++)
				m[c] = m[c] + A(i, k) * B(k, j);
		}

	this->columns = B.columns;
	this->m = m;

	return (*this);
}

ostream& operator <<(ostream& out, matrix &m) {
	return out << &m;
}

ostream& operator <<(ostream& out, matrix *m) {
	int i, j;
	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->columns; j++) {
			out << m->get(i, j) << ' ';
		}
		out << endl;
	}
	return out;
}
