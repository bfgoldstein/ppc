#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "mandelbrot.h"

using namespace std;

int main(int argc, char*argv[]) {

	int width, heigth;
	float radius;
	float x, y;

	ifstream in("mandelbrot.in");

	in >> width >> heigth;
	in >> radius;
	in >> x >> y;
	complex<float> center(x, y);

	mandelbrot m(width, heigth, radius, center);

	ofstream out("mandelbrot.out");
	out << m;
	out.close();

	return EXIT_SUCCESS;
}
