#include"component_labeling.hh"
#include<iostream>
using namespace std;
void fill(long unsigned int** output,const long unsigned int h,const long unsigned int n,const long unsigned int** input,const long unsigned int i,const long unsigned int j,const long unsigned int x) {
	if(input[i][j]>h&&output[i][j]==0) {
		output[i][j]=x;
		if(i>0) {
			fill(output,h,n,input,i-1,j,x);
		}
		if(j>0) {
			fill(output,h,n,input,i,j-1,x);
		}
		if(j<n-1) {
			fill(output,h,n,input,i,j+1,x);
		}
		if(i<n-1) {
			fill(output,h,n,input,i+1,j,x);
		}
	}
}
void component_labeling(int argc,char* argv[],long unsigned int** output,const long unsigned int n,const long unsigned int** input) {
	long unsigned int x=0;
	long unsigned int max=0;
	for(long unsigned int i=0;i<n;++i) {
		for(long unsigned int j=0;j<n;++j) {
			if(input[i][j]>max) {
				max=input[i][j];
			}
		}
	}
	for(long unsigned int h=0;h<max;++h) {
		for(long unsigned int i=0;i<n;++i) {
			for(long unsigned int j=0;j<n;++j) {
				output[i][j]=0;
			}
		}
		for(long unsigned int i=0;i<n;++i) {
			for(long unsigned int j=0;j<n;++j) {
				if(input[i][j]>h&&output[i][j]==0) {
					fill(output,h,n,input,i,j,++x);
				}
			}
		}
	}
	cout<<"x="<<x<<endl;
}

