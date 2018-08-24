#ifndef BIGDECIMAL_H_
#define BIGDECIMAL_H_

#include <deque>
#include <string>

using namespace std;

class bigdecimal {
private:
	deque<int> *digits;
	uint places, dot;
	int signal;

	bigdecimal() {
		digits = new deque<int> ();
		dot = 0;
		signal = 1;
	}
	;

	// methods
	void remove_leading_zeros();
	void remove_trailing_zeros();
	void round();

public:
	// constructors
	bigdecimal(const char *, int);
	bigdecimal(string &, int);

	// destructors
	virtual ~bigdecimal();

	// operator
	ostream& operator <<(ostream&);
	bigdecimal* operator+(bigdecimal&);
	bigdecimal* operator+(bigdecimal*);
	bigdecimal* operator-(bigdecimal&);
	bigdecimal* operator-(bigdecimal*);
	bigdecimal* operator*(bigdecimal&);
	bigdecimal* operator*(bigdecimal*);
	bigdecimal* operator/(bigdecimal&);
	bigdecimal* operator/(bigdecimal*);
	bool operator>(bigdecimal&);
	bool operator>(bigdecimal*);
	bool operator<(bigdecimal&);
	bool operator<(bigdecimal*);
	bool operator<=(bigdecimal&);
	bool operator<=(bigdecimal*);
	bool operator==(bigdecimal&);
	bool operator==(bigdecimal*);
	bool operator!=(bigdecimal&);
	bool operator!=(bigdecimal*);
	bigdecimal *operator<<(int);

};

// general

ostream& operator <<(ostream& out, bigdecimal &decimal);
ostream& operator <<(ostream& out, bigdecimal *decimal);

#endif /* BIGDECIMAL_H_ */
