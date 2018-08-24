#include"life.hh"
#include<iostream>
#include<sys/time.h>
#include<time.h>
using namespace std;
int main(int argc,char* argv[],char* envp) try {
	struct timeval timevalA;
	struct timeval timevalB;

	long unsigned int n;
	cin>>n;
	long unsigned int generations;
	bool** input=new bool*[n];
	for(long unsigned int i=0;i<n;++i) {
		input[i]=new bool[n];
		for(long unsigned int j=0;j<n;++j) {
			cin>>input[i][j];
		}
	}
	bool** output=new bool*[n];
	for(long unsigned int i=0;i<n;++i) {
		output[i]=new bool[n];
		for(long unsigned int j=0;j<n;++j) {
			output[i][j]=false;
		}
	}
	cin>>generations;

	gettimeofday(&timevalA,NULL);
	life(argc,argv,output,(const long unsigned int)generations,(const long unsigned int)n,(const bool**)input);
	gettimeofday(&timevalB,NULL);

	cout<<timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000<<endl;

	for(long unsigned int i=0;i<n;++i) {
		for(long unsigned int j=0;j<n;++j) {
			if(j) {
				cout<<" ";
			}
			cout<<output[i][j];
		}
		cout<<endl;
	}

	return EXIT_SUCCESS;
}
catch(...) {
	cerr<<"EXIT_FAILURE";
	return EXIT_FAILURE;
}

