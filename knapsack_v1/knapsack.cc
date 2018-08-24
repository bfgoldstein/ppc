#include"knapsack.hh"
#include<algorithm>
#include<bitset>
#include<iostream>
#include<vector>
using namespace std;
class comparator {
	public:
		bool operator()(const item* a,const item* b) const {
			return a->weight*b->volume>a->volume*b->weight;
		}
};
void knapsack(int argc,char* argv[],long unsigned int* output,const long unsigned int capacity,const long unsigned int n,const item* items) {
	vector<const item*> v;
	v.reserve(n);
	for(long unsigned int i=0;i<n;++i) {
		v.push_back(&items[i]);
	}
	sort(v.begin(),v.end(),comparator());
	vector<long unsigned int> sum;
	sum.reserve(n);
	long unsigned int s=0;
	for(vector<const item*>::reverse_iterator it=v.rbegin();it!=v.rend();++it) {
		s+=(*it)->weight;
		sum.push_back(s);
	}
	reverse(sum.begin(),sum.end());
	bitset<32768> bitsetA;
	bitset<32768> best;

	long unsigned int bestvalue=0;
	long unsigned int weight=0;
	long unsigned int volume=0;
	int i=0;
	do {
		while(i<n) {
			if(volume+v[i]->volume<=capacity&&weight+sum[i]>bestvalue) {
				bitsetA.set(i);
				weight+=v[i]->weight;
				volume+=v[i]->volume;
			}
			++i;
		}
		if(weight>bestvalue) {
			best=bitsetA;
			bestvalue=weight;
		}
		while(!bitsetA.test(--i));
		bitsetA.reset(i);
		weight-=v[i]->weight;
		volume-=v[i]->volume;
		++i;
	} while(bitsetA.any());
	for(i=0;i<n;i++) {
		output[v[i]-items]=best.test(i);
//		if(best.test(i)) {
//			cout<<items[v[i]-items].volume<<endl;
//		}
	}
}

