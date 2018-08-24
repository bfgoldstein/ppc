#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <set>
#include <map>
#include <iostream>

using namespace std;

set<set<unsigned int> > output;

void to_ind(unsigned int n, const set<set<unsigned int> > superset, map<set<
		unsigned int> , set<unsigned int> >& ind2) {
	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = i + 1; j < n; j++) {
			set<unsigned int> s, k;
			s.insert(i);
			k.insert(i);
			k.insert(j);
			if (superset.find(k) == superset.end())
				ind2[s].insert(j);
			s.clear();
			k.clear();
		}
	}
}

int is_ind(const set<unsigned int> s, const set<set<unsigned int> > superset) {
	for (set<unsigned int>::iterator it1 = s.begin(); it1 != s.end(); it1++) {
		for (set<unsigned int>::iterator it2 = it1; it2 != s.end(); it2++) {
			if (*it1 != *it2) {
				set<unsigned int> t;
				t.insert(*it1);
				t.insert(*it2);
				if (superset.find(t) != superset.end())
					return (0);
				t.clear();
			}
		}
	}
	return (1);
}

void search(const set<set<unsigned int> > superset, map<set<unsigned int> ,
		set<unsigned int> >& ind) {
	do {
		map<set<unsigned int> , set<unsigned int> > next;
		for (map<set<unsigned int> , set<unsigned int> >::iterator it1 =
				ind.begin(); it1 != ind.end(); it1++) {
			for (set<unsigned int>::iterator it2 = (it1->second).begin(); it2
					!= (it1->second).end(); it2++) {
				for (set<unsigned int>::iterator it3 = it2; it3
						!= (it1->second).end(); it3++) {
					if (*it3 != *it2) {
						set<unsigned int> s, k;
						for (set<unsigned int>::iterator it4 =
								(it1->first).begin(); it4 != (it1->first).end(); it4++) {
							s.insert(*it4);
							k.insert(*it4);
						}
						s.insert(*it2);
						k.insert(*it2);
						k.insert(*it3);
						int sub_ind = 1;
						sub_ind = is_ind(k, superset);
						if (sub_ind)
							next[s].insert(*it3);
						s.clear();
					}
				}
			}
		}
		if (next.size() == 0) {
			for (map<set<unsigned int> , set<unsigned int> >::iterator it1 =
					ind.begin(); it1 != ind.end(); it1++) {
				for (set<unsigned int>::iterator it2 = (it1->second).begin(); it2
						!= (it1->second).end(); it2++) {
					set<unsigned int> s;
					for (set<unsigned int>::iterator it3 = (it1->first).begin(); it3
							!= (it1->first).end(); it3++)
						s.insert(*it3);
					s.insert(*it2);
					output.insert(s);
				}
			}
		}
		ind.clear();
		for (map<set<unsigned int> , set<unsigned int> >::iterator it1 =
				next.begin(); it1 != next.end(); it1++) {
			for (set<unsigned int>::iterator it2 = (it1->second).begin(); it2
					!= (it1->second).end(); it2++) {
				set<unsigned int> s;
				for (set<unsigned int>::iterator it3 = (it1->first).begin(); it3
						!= (it1->first).end(); it3++)
					s.insert(*it3);
				ind[s].insert(*it2);
				s.clear();
			}
		}
		next.clear();
	} while (ind.size() > 0);
}

void count(const set<set<unsigned int> >& superset, const unsigned int n) {
	map<set<unsigned int> , set<unsigned int> > ind;
	to_ind(n, superset, ind);
	search(superset, ind);
}

int main(int argc, char* argv[], char* envp[]) {
	unsigned int n;
	set<set<unsigned int> > superset;

	FILE* f = stdin;
	fscanf(f, "%d", &n);
	while (!feof(f)) {
		unsigned int a, b;
		fscanf(f, "%d", &a);
		fscanf(f, "%d", &b);
		set<unsigned int> s;
		s.insert(a);
		s.insert(b);
		superset.insert(s);
		s.clear();
	}
	fclose(f);

	count(superset, n);

	cout << output.size();

	return EXIT_SUCCESS;
}
