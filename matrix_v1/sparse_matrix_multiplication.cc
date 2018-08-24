#include "sparse_matrix_multiplication.hh"
#include<ext/hash_map>
#include<iostream>
#include<vector>
using namespace __gnu_cxx;
using namespace std;
typedef struct {
	bool operator()(const entry* a,const entry* b) const {
		long int difference;
		if((difference=a->row-b->row)) {
			return difference<0;
		}
		if((difference=a->column-b->column)) {
			return difference<0;
		}
		return 0;
	}
} pointer_comparator;
typedef struct {
	bool operator()(const entry& a,const entry& b) const {
		long int difference;
		if((difference=a.row-b.row)) {
			return difference<0;
		}
		if((difference=a.column-b.column)) {
			return difference<0;
		}
		return 0;
	}
} comparator;
typedef struct {
	long unsigned int operator()(const entry& a) const {
		return (a.column<<16)^(a.row);
	}
} hash_function;
typedef struct {
	long unsigned int operator()(const entry& a,const entry& b) const {
		return a.column==b.column&&a.row==b.row;
	}
} equal_key;
void sparse_matrix_multiplication(long unsigned int* ab_entries,entry* ab,const long unsigned int a_rows,const long unsigned int a_columns_b_rows,const long unsigned int b_rows,const long unsigned int a_entries,const long unsigned int b_entries,const entry* a,const entry* b) {
	vector<const entry*> vectorA;
	vectorA.reserve(a_entries);
	vector<const entry*> vectorB;
	vectorB.reserve(b_entries);
	for(long unsigned int i=0;i<a_entries;++i) {
		vectorA.push_back(&a[i]);
	}
	for(long unsigned int i=0;i<b_entries;++i) {
		vectorB.push_back(&b[i]);
	}
	pointer_comparator comparatorA;
	sort(vectorA.begin(),vectorA.end(),comparatorA);
	sort(vectorB.begin(),vectorB.end(),comparatorA);
	hash_map<entry,long unsigned int,hash_function,equal_key> c_values;
	for(vector<const entry*>::iterator itA=vectorA.begin();itA!=vectorA.end();++itA) {
		entry probe;
		probe.row=(*itA)->column;
		probe.column=0;
		for(vector<const entry*>::iterator itB=lower_bound(vectorB.begin(),vectorB.end(),&probe,comparatorA);itB!=vectorB.end()&&(*itB)->row==(*itA)->column;++itB) {
			entry c_entry;
			c_entry.row=(*itA)->row;
			c_entry.column=(*itB)->column;
			c_entry.value=0;
			c_values[c_entry]+=(*itA)->value*(*itB)->value;
//			cout<<"multiplying a["<<(*itA)->row<<","<<(*itA)->column<<"] ("<<(*itA)->value<<") and b["<<(*itB)->row<<","<<(*itB)->column<<"] ("<<(*itB)->value<<") and adding to c["<<c_entry.row<<","<<c_entry.column<<"] ("<<c_values[c_entry]<<")"<<endl;
		}
	}
	*ab_entries=c_values.size();
	vector<entry> c_vector;
	c_vector.reserve(*ab_entries);
	for(hash_map<entry,long unsigned int,hash_function,equal_key>::iterator itC=c_values.begin();itC!=c_values.end();++itC) {
		entry e;
		e.row=itC->first.row;
		e.column=itC->first.column;
		e.value=itC->second;
		c_vector.push_back(e);
	}
	comparator comparatorB;
	sort(c_vector.begin(),c_vector.end(),comparatorB);
	for(int i=0;i<*ab_entries;++i) {
		ab[i].row=c_vector[i].row;
		ab[i].column=c_vector[i].column;
		ab[i].value=c_vector[i].value;
//		cout<<ab[i].row<<","<<ab[i].column<<":"<<ab[i].value<<endl;
	}
}

