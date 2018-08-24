#include <iostream>
#include "pi.h"

using namespace std;

int main() {

	int places;

        cin >> places;

	pi PI(places);

	cout << PI << endl;

	return 0;
}

