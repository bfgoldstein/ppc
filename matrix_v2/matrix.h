#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>

using namespace std;

class matrix {
private:
	int *m;
	int rows, columns;

	inline int operator()(int row, int column) {
		return m[row * columns + column];
	}

public:
	matrix(int, int);
	virtual ~matrix();

	matrix& operator*(matrix&);
	friend ostream& operator <<(ostream&, matrix&);
	friend ostream& operator <<(ostream&, matrix*);

	// methods
	inline int get(int row, int column) {
		if (row < 0 || row >= rows)
			throw row;
		if (column < 0 || column >= columns)
			throw column;
		return m[row * columns + column];
	}

	inline void set(int row, int column, int value) {
		if (row < 0 || row >= rows)
			throw row;
		if (column < 0 || column >= columns)
			throw column;
		m[row * columns + column] = value;
	}
};

#endif /* MATRIX_H_ */
