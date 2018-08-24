#ifndef PI_H_
#define PI_H_

#include <iostream>
#include <string>
#include "bigdecimal.h"

using namespace std;

class pi {
private:
	bool ok;
	int places;
	bigdecimal *result;

	void run();
	bigdecimal *arccot(bigdecimal *);

public:
	pi(int);
	~pi();

	ostream& operator <<(ostream &);
};

ostream& operator <<(ostream& out, pi &p);
ostream& operator <<(ostream& out, pi *p);

#endif /* PI_H_ */
