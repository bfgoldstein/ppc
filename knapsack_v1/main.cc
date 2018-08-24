#include<iostream>
#include<sys/time.h>
#include<time.h>
#include"knapsack.hh"
using namespace std;
int main(int argc,char* argv[],char* envp) try {
	struct timeval timevalA;
	struct timeval timevalB;

	long unsigned int capacity;
	long unsigned int n;
	cin>>capacity;
	cin>>n;
	long unsigned int* output=new long unsigned int[n];
	item* items=new item[n];
	for(long unsigned int i=0;i<n;++i) {
		item& itemA=items[i];
		cin>>itemA.weight;
		cin>>itemA.volume;
		output[i]=0;
	}

	gettimeofday(&timevalA,NULL);
	knapsack(argc,argv,output,capacity,n,items);
	gettimeofday(&timevalB,NULL);

	long unsigned int count=0;
	long unsigned int volume=0;
	long unsigned int weight=0;
	for(int i=0;i<n;++i) {
		if(output[i]!=0) {
			++count;
			volume+=items[i].volume;
			weight+=items[i].weight;
		}
	}
	cout<<"count="<<count<<", volume="<<volume<<", weight="<<weight<<endl;

	cout<<timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000<<endl;

	return EXIT_SUCCESS;
}
catch(...) {
	cerr<<"EXIT_FAILURE"<<endl;
	return EXIT_FAILURE;
}

