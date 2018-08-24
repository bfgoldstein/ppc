#include"convex_hull.hh"
#include<iostream>
#include<sys/time.h>
#include<time.h>
using namespace std;
int main(int argc,char* argv[],char* envp) try {
	struct timeval timevalA;
	struct timeval timevalB;

	long unsigned int n;
	cin>>n;
	point* input=new point[n];
	point* output=new point[n];
	for(long unsigned int i=0;i<n;++i) {
		cin>>input[i].x;
		cin>>input[i].y;
	}
	long unsigned int h;

	gettimeofday(&timevalA,NULL);
	int convex_hulls=0;
	while(n>0) {
		convex_hull(argc,argv,&h,output,(const long unsigned int)n,(const point*)input);
		++convex_hulls;
		for(long unsigned int i=0;i<h;++i) {
			for(long unsigned int j=0;j<n;++j) {
				if(output[i].x==input[j].x&&output[i].y==input[j].y) {
					while(j<n-1) {
						input[j].x=input[j+1].x;
						input[j].y=input[j+1].y;
						j++;
					}
					break;
				}
			}
		}
		n-=h;
	}
	cout<<"convex hulls="<<convex_hulls<<endl;
	gettimeofday(&timevalB,NULL);

	cout<<timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000<<endl;

	return EXIT_SUCCESS;
}
catch(...) {
	cerr<<"EXIT_FAILURE";
	return EXIT_FAILURE;
}

