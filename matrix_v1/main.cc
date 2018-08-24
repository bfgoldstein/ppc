#include<iostream>
#include<sys/time.h>
#include<time.h>
using namespace std;
typedef struct {
	long unsigned int row;
	long unsigned int column;
	long unsigned int value;
} entry;
void sparse_matrix_multiplication(long unsigned int*,entry*,const long unsigned int,const long unsigned int,const long unsigned int,const long unsigned int,const long unsigned int,const entry*,const entry*);
int main(int argc,char* argv[],char* envp) try {
	struct timeval timevalA;
	struct timeval timevalB;

	long unsigned int a_rows;
	long unsigned int a_columns_b_rows;
	long unsigned int b_columns;
	long unsigned int a_entries;
	long unsigned int b_entries;
	long unsigned int ab_entries;
	entry* a;
	entry* b;
	entry* ab;
	cin>>a_rows;
	cin>>a_columns_b_rows;
	cin>>a_entries;
	a=new entry[a_entries];
	for(long unsigned int i=0;i<a_entries;++i) {
		cin>>a[i].row;
		cin>>a[i].column;
		cin>>a[i].value;
	}
	cin>>a_columns_b_rows;
	cin>>b_columns;
	cin>>b_entries;
	b=new entry[b_entries];
	for(long unsigned int i=0;i<b_entries;++i) {
		cin>>b[i].row;
		cin>>b[i].column;
		cin>>b[i].value;
	}
	ab=new entry[a_rows*b_columns];
	gettimeofday(&timevalA,NULL);
	sparse_matrix_multiplication(&ab_entries,ab,(const long unsigned int)a_rows,(const long unsigned int)a_columns_b_rows,(const long unsigned int)b_columns,(const long unsigned int)a_entries,(const long unsigned int)b_entries,(const entry*)a,(const entry*)b);
	gettimeofday(&timevalB,NULL);

	cout<<"time="<<timevalB.tv_sec-timevalA.tv_sec+(timevalB.tv_usec-timevalA.tv_usec)/(double)1000000<<endl;

	return EXIT_SUCCESS;
}
catch(...) {
	cerr<<"EXIT_FAILURE";
	return EXIT_FAILURE;
}

