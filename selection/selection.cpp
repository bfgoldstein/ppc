// Serial version of Selection algorithm
// The Art of Concurrency / Clay Breshears
// Modified: Denise Stringhini

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/time.h>

using namespace std;

#define Q 5     // Assumes fixed value of five; Modifiy 'Q' functions if value is other than five
unsigned long N, k;
int *S;

//prototypes
int SortSelect2(int[], int);
int SortSelect3(int[], int);
int SortSelect4(int[], int);
int SortSelect5(int[], int);
void CountAndMark(int[], int[], int, int, int[]);
void ArrayPack(int[], int[], int, int[], int);

int SortLessThanQ(int S[], int num, int k) {
	switch (num) {
	case 1:
		return S[0];
		break;
	case 2:
		return SortSelect2(S, k);
		break;
	case 3:
		return SortSelect3(S, k);
		break;
	case 4:
		return SortSelect4(S, k);
		break;
	case 5:
		return SortSelect5(S, k);
		break;
	default:
		printf("SortLessThanQ Error: num not in [1..4]   num = %d\n", num);
		return -1;
	}
}

int SequentialSelect(int *S, int num, int k) {
	if (num <= Q)
		return SortLessThanQ(S, num, k);

	int cNum = num / Q + 1;
	int *Medians = new int[cNum];
	int i = 0;
	for (int j = 0; j < num / Q; j++) {
		Medians[j] = SortSelect5(&S[i], 3);  // find medians of subsequences
		i += Q;
	}
	int lastNum = num - (Q * (num / Q));
	if (lastNum) {
		int lastQ = Q * (num / Q);
		Medians[cNum - 1] = SortLessThanQ(&S[lastQ], lastNum,
				(lastNum + 1) / 2);
	} else
		cNum--;

	int M = SequentialSelect(Medians, cNum, (cNum + 1) / 2);
	delete Medians;

	int leg[3] = { 0, 0, 0 };
	int *markS = new int[num];
	CountAndMark(S, markS, num, M, leg);

	if (leg[0] >= k) {
		int *sPack = new int[leg[0]];
		ArrayPack(S, sPack, num, markS, 0);
		delete markS;
		M = SequentialSelect(sPack, leg[0], k);
		delete sPack;
		return M;
	} else if ((leg[0] + leg[1]) >= k) {
		delete markS;
		return M;
	} else {
		int *sPack = new int[leg[2]];
		ArrayPack(S, sPack, num, markS, 2);
		delete markS;
		M = SequentialSelect(sPack, leg[2], k - (leg[0] + leg[1]));
		delete sPack;
		return M;

	}
}

void init_data() {
	cin >> k;
	cin >> N;

	unsigned int i;
	S = new int[N];

	for (i = 0; i < N; i++)
		cin >> S[i];
}

int main(int argc, char* argv[]) {

	init_data();

	int i = SequentialSelect(S, N, k);

	cout << "i = " << i << endl;

	return 0;
}

#define swap(A,B) {int t; t = A; A = B; B = t;}

int SortSelect2(int S[], int k) {
	if (S[0] > S[1])
		swap(S[0], S[1]);
	if (k == 1)
		return S[0];
	else
		return S[1];
}

int SortSelect3(int S[], int k) {
	if (S[0] > S[1])
		swap(S[0], S[1]);
	if (S[1] > S[2])
		swap(S[1], S[2]);
	if (S[0] > S[1])
		swap(S[0], S[1]);
	return S[k - 1];
}

int SortSelect4(int S[], int k) {
	if (S[0] > S[1])
		swap(S[0], S[1]);
	if (S[1] > S[2])
		swap(S[1], S[2]);
	if (S[0] > S[1])
		swap(S[0], S[1]);
	if (S[2] > S[3])
		swap(S[2], S[3]);
	if (S[1] > S[2])
		swap(S[1], S[2]);
	if (S[0] > S[1])
		swap(S[0], S[1]);
	return S[k - 1];
}

int SortSelect5(int S[], int k) {
	if (S[0] > S[1])
		swap(S[0], S[1]);
	if (S[1] > S[2])
		swap(S[1], S[2]);
	if (S[0] > S[1])
		swap(S[0], S[1]);
	if (S[2] > S[3])
		swap(S[2], S[3]);
	if (S[1] > S[2])
		swap(S[1], S[2]);
	if (S[0] > S[1])
		swap(S[0], S[1]);
	if (S[3] > S[4])
		swap(S[3], S[4]);
	if (S[2] > S[3])
		swap(S[2], S[3]);
	if (S[1] > S[2])
		swap(S[1], S[2]);
	if (S[0] > S[1])
		swap(S[0], S[1]);

	return S[k - 1];
}

void CountAndMark(int S[], int Marks[], int num, int median, int leg[3]) {
	for (int i = 0; i < num; i++) {
		if (S[i] == median) {
			Marks[i] = 1;
			leg[1]++;
		} else if (S[i] < median) {
			Marks[i] = 0;
			leg[0]++;
		} else {
			Marks[i] = 2;
			leg[2]++;
		}
	}
}

void ArrayPack(int S[], int sPack[], int num, int Marks[], int scanSym) {
	int i, j = 0;
	for (i = 0; i < num; i++)
		if (Marks[i] == scanSym)
			sPack[j++] = S[i];
}

