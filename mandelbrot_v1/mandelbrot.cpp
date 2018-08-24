/*
 * Based on Java Applet from http://aleph0.clarku.edu/~djoyce/julia/MandelbrotApplet.html
 */

#include "mandelbrot.h"

void mandelbrot::init() {
	resolution = 500;
	radius = 2;
	scale = 2;
	center = complex<float>(0,0);

	plane = MU_;
	escape = HALFPLANE;
	pattern = GRAYSCALE;

	update = true;
	bound = PATTERN_VALUE[pattern];
	bound2 = bound * bound;

	img = NULL;
}

complex<float> mandelbrot::convert(complex<float> &z, PLANE oldPlane,
		PLANE newPlane) {

	complex<float> r = z;

	if (oldPlane == newPlane)
		return r;
	// first convert from the old plane to either the lambda or the mu plane
	if (oldPlane != MU_ && oldPlane != LAMBDA) {
		r = complex<float>(r.real() / norm(r), r.imag() / norm(r));
		if (oldPlane == RECIPMUPLUSFOURTH)
			r = complex<float>(r.real() - 0.25, r.imag());
		else if (oldPlane == RECIPLAMBDAMINUSONE)
			r = complex<float>(r.real() + 1, r.imag());
		else if (oldPlane == RECIPMUMINUSMYER)
			r = complex<float>(r.real() + MYERBERG, r.imag());
	} // if
	  // next, convert to mu or lambda as necessary
	if (oldPlane == LAMBDA || oldPlane == RECIPLAMBDA
			|| oldPlane == RECIPLAMBDAMINUSONE) {
		if (newPlane != LAMBDA && newPlane != RECIPLAMBDA
				&& newPlane != RECIPLAMBDAMINUSONE) {
			// convert lambda to mu. mu = (lambda/2)^2 - (lambda/2)
			r = complex<float>(r.real() / 2.0, r.imag() / 2.0);
			r = r * r - r;
		} // if
	} else {
		if (newPlane == LAMBDA || newPlane == RECIPLAMBDA
				|| newPlane == RECIPLAMBDAMINUSONE) {
			// convert mu to lambda. lambda = 1 + sqrt(1+4mu)
			r = complex<float>(r.real() * 4.0, r.imag() * 4.0);
			r = complex<float>(r.real() + 1, r.imag());
			r = sqrt(r);
			r = complex<float>(r.real() + 1, r.imag());
		} // if
	} // if/else
	  // finally, convert to the new plane
	switch (newPlane) {
	case MU_:
		return r;
	case LAMBDA:
		return r;
	case RECIPMU:
		return complex<float>(r.real() / norm(r), r.imag() / norm(r));
	case RECIPMUPLUSFOURTH:
		r = complex<float>(r.real() + 0.25, r.imag());
		return complex<float>(r.real() / norm(r), r.imag() / norm(r));
	case RECIPLAMBDA:
		return complex<float>(r.real() / norm(r), r.imag() / norm(r));
	case RECIPLAMBDAMINUSONE:
		r = complex<float>(r.real() - 1.0, r.imag());
		return complex<float>(r.real() / norm(r), r.imag() / norm(r));
	case RECIPMUMINUSMYER:
		r = complex<float>(r.real() - MYERBERG,r.imag());
		return complex<float>(r.real() / norm(r), r.imag() / norm(r));
	} // switch
	return z;
}

complex<float> mandelbrot::convert(int x, int y) {
	double minWH = width < height ? width : height;
	double factor = radius / minWH;
	complex<float> r((2.0 * x - width) * factor, (height - 2.0 * y) * factor);
	return r * center;
}

bool mandelbrot::escaped(float s, float t) {
	switch (escape) {
	case CIRCLE:
		return s * s + t * t >= bound2;
	case SQUARE:
		return abs(s) >= bound || abs(t) >= bound;
	case STRIP:
		return abs(s) >= bound;
	case HALFPLANE:
		return s >= bound;
	} // switch
	return true; // never used, but makes compiler happy
}

char mandelbrot::valueAt(float x, float y) {
	complex<float> z(x, y);

	z = convert(z, plane, MU_);
	x = z.real();
	y = z.imag();

	// Next check to see if z + 1/4 lies inside the cardioid
	// given by the polar inequality r < (1+cos theta)/2. In rectangular
	// coordinates this becomes (s^2 + t^2 - s/2)^2 < (s^2 + t^2)/4 where
	// (s,t) is (x + 1/4, y). If so, z lies inside the set
	float s = x + 0.25;
	float t = y;
	float ss = s * s;
	float tt = y * y;
	float left = (ss + tt - s * 0.5);
	if (left * left < (ss + tt) * 0.25)
		return BLACK;

	// Now see how many iterates of 0 it takes to reach the escape criterion
	// These computations do not use the Complex class for sake of speed
	s = 0.0;
	t = 0.0;
	int k = 0;
	for (k = 0; !escaped(s, t) && k < resolution; k++) {
		ss = s * s - t * t;
		tt = 2.0 * s * t;
		s = ss - x;
		t = tt - y;
	} // for

	if (k == resolution)
		return BLACK;

	if (pattern == ZEBRA)
		return (k % 2 == 0) ? BLACK : WHITE;

	if (pattern == FEATHERED) {
		if (abs(s) < bound || abs(t) < bound)
			return BLACK;
	}

	if (pattern == GRAYSCALE) {
		float bright = (k % resolution) / (0.0 + resolution);
		if (bright < 0.5)
			bright = 1.0 - 1.2 * bright;
		else
			bright = -0.2 + 1.2 * bright;
		// bright [0,1]
		if (bright < 0.16)
			return BLACK;
		else if (bright < 0.33)
			return '.';
		else if (bright < 0.5)
			return 'o';
		else if (bright < 0.66)
			return 'O';
		else if (bright < 0.83)
			return '0';
		else
			return WHITE;
	}

	float hue = (k % resolution) / (0.0 + resolution);
	if (pattern == BINARY && t > 0)
		hue = (hue < 0.8) ? hue + 0.2 : hue - 0.8;
	if (hue < 0.16)
		return BLACK;
	else if (hue < 0.33)
		return '.';
	else if (hue < 0.5)
		return 'o';
	else if (hue < 0.66)
		return 'O';
	else if (hue < 0.83)
		return '0';
	else
		return WHITE;

}

void mandelbrot::fill(int x, int y, int width, int height, char color) {
	for (int i = x; i < x + width && i < this->width; i++) {
		if (i < 0) {
			i = -1;
			continue;
		}
		for (int j = y; j < y + height && j < this->height; j++) {
			if (j < 0) {
				j = -1;
				continue;
			}
			*(img + (this->height * i) + j) = color;
		}
	}
}

void mandelbrot::create() {
	if (!update)
		return;

	img = new char[width * height];;

	float minWH = width < height ? width : height;
	float scale = 2.0 * radius / minWH;
	float low_x = center.real() - width * scale / 2.0;
	float low_y = center.imag() - height * scale / 2.0;

	int d = 1;
	while (d < width || d < height)
		d <<= 1;
	do {
		for (int i = 0; i < width; i += d) {
			for (int j = 0; j < height; j += d) {
				if (i % (d << 1) == 0 && j % (d << 1) == 0
						&& (i != 0 || j != 0))
					continue;
				char newColor = valueAt(low_x + i * scale, low_y + j * scale);
				if (*(img + (i * height) + j) == 0
						|| newColor != *(img + (i * height) + j)) {
					fill(i, height - j - d, d, d, newColor);
					for (int s = 0; s < d; ++s)
						if (i + s < width)
							for (int t = 0; t < d; ++t)
								if (j + t < height)
									*(img + (height * (i + s)) + j + t) =
											newColor; //c[i + s][j + t] = newColor;
				}
			}
		}
		d /= 2;
	} while (d > 0);

	update = false;
}

mandelbrot::mandelbrot(int width, int height, float radius,
		complex<float>&center) {
	init();

	this->width = width;
	this->height = height;
	this->radius = radius;
	this->center = center;
}

mandelbrot::~mandelbrot() {
	delete img;
}

ostream& operator <<(ostream& out, mandelbrot &m) {
	return out << &m;
}

ostream& operator <<(ostream& out, mandelbrot *m) {

	m->create();

	for (int i = 0; i < m->width; i++) {
		for (int j = 0; j < m->height; j++) {
			out << *(m->img + (m->height * i) + j);
		}
		out << endl;
	}

	return out;
}

