#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <set>
#include "clique.hh"
using namespace std;

int main(int argc,char* argv[],char* envp) try {
	struct timeval timevalA;
	struct timeval timevalB;

	unsigned int n;
	set<set<unsigned int> > clique2;
	set<set<unsigned int> > output;

	FILE* f=stdin;
	fscanf(f, "%d", &n);
	while(!feof(f)) {
		unsigned int a, b;
		fscanf(f, "%d", &a);
		fscanf(f, "%d", &b);
		set<unsigned int> s;
		s.insert(a);
		s.insert(b);
		clique2.insert(s);
		s.clear();
	}
	fclose(f);

	gettimeofday(&timevalA,NULL);
	clique(output, clique2, n);
	gettimeofday(&timevalB,NULL);
/*
	bool right=true;
	set<long unsigned int> components;
	for(long unsigned int i=0;right&&i<n;++i) {
		for(long unsigned int j=0;right&&j<n;++j) {
			if(output[i][j]!=0) {
				components.insert(output[i][j]);
				if(i>0) {
					if(output[i-1][j]!=0&&output[i-1][j]!=output[i][j]) {
						right=false;
					}
				}
				if(j>0) {
					if(output[i][j-1]!=0&&output[i][j-1]!=output[i][j]) {
						right=false;
					}
				}
				if(j<n-1) {
					if(output[i][j+1]!=0&&output[i][j+1]!=output[i][j]) {
						right=false;
					}
				}
				if(i<n-1) {
					if(output[i+1][j]!=0&&output[i+1][j]!=output[i][j]) {
						right=false;
					}
				}
				if(i>0) {
					if(output[i-1][j]!=0&&output[i-1][j]!=output[i][j]) {
						right=false;
					}
				}
			}
		}
	}
	cout<<"right="<<right<<endl;
	cout<<"components.size()="<<components.size()<<endl;
*/
//	for(long unsigned int i=0;i<n;++i) {
//		bool separator=false;
//		for(long unsigned int j=0;j<n;++j) {
//			if(!separator) {
//				separator=true;
//			}
//			else {
//				cout<<" ";
//			}
//			cout<<output[i][j];
//		}
//		cout<<endl;
//	}

	return EXIT_SUCCESS;
}
catch(...) {
	return EXIT_FAILURE;
}

