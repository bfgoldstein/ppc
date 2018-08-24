#include<cstdlib>
#include<iostream>
#include"life.hh"
using namespace std;
void life(int argc,char* argv[],bool** output,const long unsigned int g,const long unsigned int n,const bool** input) {
	bool** even=new bool*[n];
	bool** odd=new bool*[n];
	for(long unsigned int i=0;i<n;++i) {
		even[i]=new bool[n];
		odd[i]=new bool[n];
	}
	const bool*** present;
	bool*** future;
	present=&input;
	for(long unsigned int generation=0;generation<g;++generation) {
		future=generation&1?&odd:&even;
		for(long unsigned int i=0;i<n;++i) {
			for(long unsigned int j=0;j<n;++j) {
				long unsigned int neighbors=0;
				if(i>0) {
					if(j>0) {
						if((*present)[i-1][j-1]) {
							++neighbors;
						}
					}
					if((*present)[i-1][j]) {
						++neighbors;
					}
					if(j<n-1) {
						if((*present)[i-1][j+1]) {
							++neighbors;
						}
					}
				}
				if(j>0) {
					if((*present)[i][j-1]) {
						++neighbors;
					}
				}
				if(j<n-1) {
					if((*present)[i][j+1]) {
						++neighbors;
					}
				}
				if(i<n-1) {
					if(j>0) {
						if((*present)[i+1][j-1]) {
							++neighbors;
						}
					}
					if((*present)[i+1][j]) {
						++neighbors;
					}
					if(j<n-1) {
						if((*present)[i+1][j+1]) {
							++neighbors;
						}
					}
				}
				(*future)[i][j]=neighbors==3||(*present)[i][j]&&neighbors==2;
			}
		}
		present=(const bool***)future;
	}
	for(long unsigned int i=0;i<n;++i) {
		for(long unsigned int j=0;j<n;++j) {
			output[i][j]=(*present)[i][j];
		}
	}
}

