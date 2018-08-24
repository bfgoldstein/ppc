#ifndef MANDELBROT_H_
#define MANDELBROT_H_

#include <iostream>
#include <complex>
#include <stdlib.h>

using namespace std;

enum PLANE {
	MU_ = 0, // mu
	LAMBDA, // mu = lambda^2/4 - lambda/2
	RECIPMU, // 1/mu
	RECIPMUPLUSFOURTH, // 1/(mu+.25)
	RECIPLAMBDA, // 1/lambda
	RECIPLAMBDAMINUSONE, // 1/(lambda-1)
	RECIPMUMINUSMYER
// 1/(mu-1.401)
};

enum ESCAPE {
	CIRCLE = 0, SQUARE, STRIP, HALFPLANE
};

enum PATTERN {
	PLAIN = 0, FEATHERED, BINARY, GRAYSCALE, ZEBRA
};

enum COLORS {
	BLACK = ' ', WHITE = '#'
};

const float PATTERN_VALUE[] = { 2.0, 20.0, 5.0, 2.0, 5.0 };

const float MYERBERG = 1.401155189;

class mandelbrot {
private:
	int width;
	int height;
	int resolution;
	float radius;
	float scale;

	complex<float> center;
	PLANE plane;
	ESCAPE escape;
	PATTERN pattern;

	char *img;

	bool update;
	float bound;
	float bound2;

	void init();

	complex<float> convert(complex<float> &, PLANE, PLANE);
	complex<float> convert(int, int);
	bool escaped(float, float);
	char valueAt(float, float);
	void fill(int, int, int, int, char);
	void create();
public:
	mandelbrot(int, int, float, complex<float>&);
	virtual ~mandelbrot();

	friend ostream& operator <<(ostream&, mandelbrot&);
	friend ostream& operator <<(ostream&, mandelbrot*);
};

#endif /* MANDELBROT_H_ */
