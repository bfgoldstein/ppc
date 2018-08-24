#include "bigdecimal.h"

#include <iostream>
#include <string.h>

#define DEBUG

#ifdef DEBUG
#include <deque>
ostream& operator <<(ostream& out, deque<int> *dq) {

	cout << '[';
	for (uint i = 0; i < dq->size(); i++)
		if (i)
			cout << ',' << dq->at(i);
		else
			cout << dq->at(i);
	cout << ']';
	return out;
}
#endif

using namespace std;

// private

void bigdecimal::remove_leading_zeros() {
	while (digits->size() && digits->front() == 0 && dot > 0) {
		digits->pop_front();
		dot--;
	}
	if (!digits->size())
		signal = 0;
	if (!dot) {
		digits->push_front(0);
		dot++;
	}
}

void bigdecimal::remove_trailing_zeros() {
	while (digits->size() && digits->back() == 0 && digits->size() > dot) {
		digits->pop_back();
	}
	if (!digits->size())
		signal = 0;
}

void bigdecimal::round() {
	if (!signal)
		return;
	uint size = digits->size() - dot;
	if (size <= places)
		return;
	uint dif = size - places;
	int number;
	while (dif) {
		number = digits->back();
		digits->pop_back();
		dif--;
	}
	if (number >= 5)
		digits->operator[](digits->size() - 1)++;
}

//public

bigdecimal::bigdecimal(const char *number, int places) {
	digits = new deque<int> ();
	int d = strlen(number);
	int i = 0;
	if (number[0] == '-') {
		this->signal = -1;
		i = 1;
	} else
		this->signal = 1;
	while (number[i] != '.' && i < d) {
		digits->push_back(number[i] - '0');
		i++;
	}
	if (i < d) {
		dot = i;
		i++;
		while (i < d) {
			digits->push_back(number[i] - '0');
			i++;
		}
	} else
		dot = digits->size();
	this->places = places;
	remove_leading_zeros();
	remove_trailing_zeros();
}

bigdecimal::bigdecimal(string &number, int places) {
	bigdecimal(number.c_str(), places);
}

bigdecimal::~bigdecimal() {
	delete digits;
}

ostream& bigdecimal::operator <<(ostream& os) {

	uint i;
	if (signal < 0)
		os << '-';
	else if (signal == 0) {
		os << '0';
		return os;
	}
	if (dot != digits->size()) {
		for (i = 0; i < dot; i++)
			os << (char) (digits->operator[](i) + '0');

		if (i == 0)
			os << '0';
		os << '.';
		for (; i < digits->size(); i++)
			os << (char) (digits->operator[](i) + '0');
	} else
		for (i = 0; i < digits->size(); i++)
			os << (char) (digits->operator[](i) + '0');

	return os;
}

bigdecimal* bigdecimal::operator+(bigdecimal& decimal) {

	if (signal != decimal.signal)
		return this->operator-(decimal);

	bigdecimal *r = new bigdecimal();

	int up, down, ac, sum;
	up = digits->size() - dot - 1;
	down = decimal.digits->size() - decimal.dot - 1;
	ac = 0;
	// decimal add
	while (up >= 0 || down >= 0) {
		if (up == down) {
			sum = (digits->operator[](dot + up) + decimal.digits->operator[](
					decimal.dot + down) + ac);
			r->digits->push_front(sum % 10);
			ac = sum / 10;
			up--;
			down--;
		} else if (up > down) {
			sum = (digits->operator[](dot + up) + ac);
			r->digits->push_front(sum % 10);
			ac = sum / 10;
			up--;
		} else {
			sum = (decimal.digits->operator[](decimal.dot + down) + ac);
			r->digits->push_front(sum % 10);
			ac = sum / 10;
			down--;
		}
	}
	up = dot - 1;
	down = decimal.dot - 1;
	// normal add
	while (up >= 0 && down >= 0) {
		sum = (digits->operator[](up) + decimal.digits->operator[](down) + ac);
		r->digits->push_front(sum % 10);
		ac = sum / 10;
		up--;
		down--;
	}
	while (up >= 0) {
		sum = (digits->operator[](up) + ac);
		r->digits->push_front(sum % 10);
		ac = sum / 10;
		up--;
	}
	while (down >= 0) {
		sum = (decimal.digits->operator[](down) + ac);
		r->digits->push_front(sum % 10);
		ac = sum / 10;
		down--;
	}

	if (ac)
		r->digits->push_front(ac);

	r->dot = dot > decimal.dot ? dot : decimal.dot;
	r->places = places > decimal.places ? places : decimal.places;
	r->signal = signal;

	r->remove_leading_zeros();

	return r;
}

bigdecimal* bigdecimal::operator+(bigdecimal* decimal) {
	return (*this) + (*decimal);
}

bigdecimal* bigdecimal::operator-(bigdecimal& decimal) {

	bigdecimal *r = new bigdecimal();
	bigdecimal *big, *little;

	big = this;
	little = &decimal;
	if (decimal > this) {
		big = &decimal;
		little = this;
	}

	int up, down, borrow, sub;
	up = big->digits->size() - big->dot - 1;
	down = little->digits->size() - little->dot - 1;
	borrow = 0;
	// decimal sub
	while (up >= 0 || down >= 0) {
		if (up == down) {
			sub = (big->digits->operator[](big->dot + up) - borrow + 10
					- little->digits->operator[](little->dot + down));
			r->digits->push_front(sub % 10);
			borrow = !(sub / 10);
			up--;
			down--;
		} else if (up > down) {
			sub = (big->digits->operator[](big->dot + up) - borrow + 10);
			r->digits->push_front(sub % 10);
			borrow = !(sub / 10);
			up--;
		} else {
			sub = (-borrow + 10
					- little->digits->operator[](little->dot + down));
			r->digits->push_front(sub % 10);
			borrow = !(sub / 10);
			down--;
		}
	}

	up = big->dot - 1;
	down = little->dot - 1;
	// normal sub
	while (up >= 0 && down >= 0) {
		sub = (big->digits->operator[](up) - borrow + 10
				- little->digits->operator[](down));
		r->digits->push_front(sub % 10);
		borrow = !(sub / 10);
		up--;
		down--;
	}
	while (up >= 0) {
		sub = (big->digits->operator[](up) - borrow + 10);
		r->digits->push_front(sub % 10);
		borrow = !(sub / 10);
		up--;
	}
	while (down >= 0) {
		sub = (-borrow + 10 - little->digits->operator[](down));
		r->digits->push_front(sub % 10);
		borrow = !(sub / 10);
		down--;
	}

	r->dot = big->dot;
	r->places = big->places > little->places ? big->places : little->places;
	r->signal = big->signal;

	r->remove_leading_zeros();

	return r;
}

bigdecimal* bigdecimal::operator-(bigdecimal* decimal) {
	return (*this) - (*decimal);
}

bigdecimal* bigdecimal::operator*(bigdecimal& decimal) {

	bigdecimal *r = new bigdecimal();

	if (!signal || !decimal.signal) {
		r->signal = 0;
		return r;
	}

	int size = digits->size() + decimal.digits->size();
	int vector[size];
	memset(vector, 0, sizeof(vector));
	int i, j, z;
	for (i = digits->size() - 1; i >= 0; i--) {
		z = size - (digits->size() - i);
		for (j = decimal.digits->size() - 1; j >= 0; j--, z--)
			vector[z] += digits->at(i) * decimal.digits->at(j);
	}
	int sum, carry = 0;
	for (z = size - 1; z >= 0; z--) {
		sum = vector[z] + carry;
		vector[z] = sum % 10;
		carry = sum / 10;
	}
	if (carry)
		r->digits->push_back(carry);
	for (z = 0; z < size; z++)
		r->digits->push_back(vector[z]);

	r->dot = dot + decimal.dot;
	r->places = places > decimal.places ? places : decimal.places;
	r->signal = signal * decimal.signal;

	r->remove_leading_zeros();
	r->round();

	return r;
}

bigdecimal* bigdecimal::operator*(bigdecimal* decimal) {
	return (*this) * (*decimal);
}

bigdecimal* bigdecimal::operator/(bigdecimal& decimal) {

	bigdecimal *r = new bigdecimal();
	bigdecimal *row = new bigdecimal();
	bigdecimal *tmp = new bigdecimal();

	r->places = places;
	r->signal = signal * decimal.signal;

	int p = decimal.digits->size() - decimal.dot;
	for (uint i = digits->size() - dot; i < places + p; i++)
		digits->push_back(0);

	int a, b;
	a = dot;
	b = decimal.dot;

	dot = digits->size();
	decimal.dot = decimal.digits->size();

	uint i = 0;
	while (i < digits->size()) {
		row->digits->push_back(digits->at(i));
		row->dot = row->digits->size();

		r->digits->push_back(0);
		r->dot = r->digits->size();

		row->remove_leading_zeros();
		row->remove_trailing_zeros();

		//cout << "\nIteracao " << i << endl;
		//cout << "DEC: " << decimal.digits << endl;
		//cout << "ROW: " << row->digits << endl;
		//cout << "R: " << r->digits << endl;

		while (decimal <= row) {
			r->digits->operator[](i)++;
			tmp = row->operator-(decimal);
			delete row;
			row = tmp;
			row->signal = +1;
			//cout << "ROW: " << row->digits << endl;
			//cout << "R: " << r->digits << endl;
		}
		i++;
	}

	dot = a;
	a = digits->size() - dot;
	decimal.dot = b;
	b = decimal.digits->size() - decimal.dot;
	r->dot = r->digits->size() - (a - b);

	remove_trailing_zeros();
	r->remove_trailing_zeros();
	r->remove_leading_zeros();

	//r->round();

	delete row;

	return r;
}

bigdecimal* bigdecimal::operator/(bigdecimal* decimal) {
	return (*this) / (*decimal);
}

bool bigdecimal::operator>(bigdecimal& decimal) {

	if (dot > decimal.dot)
		return true;
	else if (dot < decimal.dot)
		return false;

	uint i = 0;
	while (digits->operator[](i) == decimal.digits->operator[](i) && i
			< digits->size() && i < decimal.digits->size())
		i++;
	if (i >= digits->size())
		return false;
	if (i >= decimal.digits->size())
		return true;
	if (digits->operator[](i) > decimal.digits->operator[](i))
		return true;

	return false;
}

bool bigdecimal::operator>(bigdecimal* decimal) {
	return (*this) > (*decimal);
}

bool bigdecimal::operator<(bigdecimal& decimal) {
	if (dot < decimal.dot)
		return true;
	else if (dot > decimal.dot)
		return false;

	uint i = 0;
	while (digits->operator[](i) == decimal.digits->operator[](i) && i
			< digits->size() && i < decimal.digits->size())
		i++;
	if (i >= digits->size())
		return true;
	if (i >= decimal.digits->size())
		return false;
	if (digits->operator[](i) < decimal.digits->operator[](i))
		return true;

	return false;
}

bool bigdecimal::operator<(bigdecimal* decimal) {
	return (*this) < (*decimal);
}

bool bigdecimal::operator<=(bigdecimal& decimal) {
	return !((*this) > decimal);
}

bool bigdecimal::operator<=(bigdecimal* decimal) {
	return (*this) <= (*decimal);
}

bool bigdecimal::operator==(bigdecimal& decimal) {
	if (dot != decimal.dot)
		return false;
	if (signal != decimal.signal)
		return false;

	if (digits->size() != decimal.digits->size())
		return false;

	for (uint i = 0; i < digits->size(); i++)
		if (digits->at(i) != decimal.digits->at(i))
			return false;

	return true;
}

bool bigdecimal::operator==(bigdecimal* decimal) {
	return (*this) == (*decimal);
}

bool bigdecimal::operator!=(bigdecimal&decimal) {
	return !((*this) == decimal);
}

bool bigdecimal::operator!=(bigdecimal*decimal) {
	return (*this) != (*decimal);
}

bigdecimal *bigdecimal::operator<<(int places) {

	if (!signal)
		return this;

	for (int i = 0; i < places; i++) {
		digits->push_back(0);
		dot++;
	}

	return this;
}

// general

ostream& operator <<(ostream& out, bigdecimal &decimal) {
	return decimal << out;
}

ostream& operator <<(ostream& out, bigdecimal *decimal) {
	return (*decimal) << out;
}

