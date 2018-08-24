#include "pi.h"

using namespace std;

pi::pi(int places) {
	ok = false;
	this->places = places;
}

pi::~pi() {
	if (ok)
		delete result;
}

void pi::run() {
	//Machin: PI/4 = 4*arctan(5)-arctan(239)

	bigdecimal *tmp;
	bigdecimal *first, *second;
	bigdecimal *four = new bigdecimal("4", places);

	// 4*arctan(5)
	first = new bigdecimal("5", places);
	tmp = arccot(first);
	delete first;
	first = (*four) * tmp;
	delete tmp;

	//arctan(239)
	tmp = new bigdecimal("239", places);
	second = arccot(tmp);
	delete tmp;

	// PI = 4*(first - second);
	tmp = (*first) - second;
	delete first;
	delete second;
	result = (*four) * tmp;
	delete tmp;

	ok = true;

	delete four;
}

bigdecimal* pi::arccot(bigdecimal *r) {
	bigdecimal zero("0", places);

	bigdecimal *term, *doble;
	bigdecimal *sum, *tmp, *div;
	bigdecimal *n = new bigdecimal("1", places);
	bigdecimal *two = new bigdecimal("2", places);
	sum = (*n) / r;
	term = (*n) / r;
	doble = (*term) * term;

	int i = 0;
	do {

		tmp = (*term) * doble;
		delete term;
		term = tmp;

		tmp = (*n) + two;
		delete n;
		n = tmp;

		div = (*term) / n;

		if (i % 2 == 0)
			tmp = (*sum) - div;
		else
			tmp = (*sum) + div;
		if ((*div) == zero) {
			delete div;
			delete sum;
			sum = tmp;
			break;
		}
		delete div;
		delete sum;
		sum = tmp;

		i++;
	} while (true);

	delete two;
	delete n;
	delete doble;
	delete term;

	return sum;
}

ostream& pi::operator <<(ostream& out) {
	if (!ok)
		run();
	out << result;
	return out;
}

// general

ostream& operator <<(ostream& out, pi &p) {
	return p << out;
}

ostream& operator <<(ostream& out, pi *p) {
	return (*p) << out;
}

