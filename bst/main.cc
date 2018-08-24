#include"obst.hh"
#include<iostream>
#include<malloc.h>
#include<sys/time.h>
#include<time.h>
using namespace std;
int main(int argc,char* argv[],char* envp) try {
	struct timeval timevalA;
	struct timeval timevalB;

	gettimeofday(&timevalA,NULL);
	int i;
	int n;
	int** root;
	float* p;
	void print_root(int**,int,int);
	fscanf(stdin,"%d",&n);
	p=(float*)malloc(n*sizeof(float));
	for(i=0;i<n;i++)
		fscanf(stdin,"%f",&p[i]);
	int* output=new int[n];
	obst(output,n,p);
	gettimeofday(&timevalB,NULL);

	for(int i=0;i<n;++i) {
		cout<<output[i]<<endl;
	}
	cout<<timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000<<endl;

	return EXIT_SUCCESS;
}
catch(...) {
	cerr<<"EXIT_FAILURE";
	return EXIT_FAILURE;
}

