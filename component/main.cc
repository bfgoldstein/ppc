#include<iostream>
#include<sys/time.h>
#include<time.h>
#include<set>
#include"component_labeling.hh"
using namespace std;
int main(int argc,char* argv[],char* envp) try {
	struct timeval timevalA;
	struct timeval timevalB;

	long unsigned int n;
	cin>>n;
	long unsigned int** output=new long unsigned int*[n];
	for(long unsigned int i=0;i<n;++i) {
		output[i]=new long unsigned int[n];
	}
	long unsigned int** array=new long unsigned int*[n];
	for(long unsigned int i=0;i<n;++i) {
		array[i]=new long unsigned int[n];
		for(long unsigned int j=0;j<n;++j) {
			cin>>array[i][j];
		}
	}

	gettimeofday(&timevalA,NULL);
	component_labeling(argc,argv,output,(const long unsigned int)n,(const long unsigned int**)array);
	gettimeofday(&timevalB,NULL);

	cout<<"time="<<timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000<<endl;

	return EXIT_SUCCESS;
}
catch(...) {
	cerr<<"EXIT_FAILURE";
	return EXIT_FAILURE;
}

