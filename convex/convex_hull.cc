#include"convex_hull.hh"
#include<deque>
//#include<ext/algorithm>
#include<iostream>
#include<set>
using namespace std;
struct rightmost_lowest {
	bool operator()(const point& a,const point& b) const {
		long int difference;
		if((difference=a.y-b.y)) {
			return difference>0;
		}
		if((difference=a.x-b.x)) {
			return difference<0;
		}
		return false;
	}
};
long int distancesquare(const point a,const point b) {
	return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}
long int left(const point a,const point b,const point c) {
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
class comparator {
	public:
		comparator(const point& reference) {
			this->reference=reference;
		}
		bool operator()(const point& a,const point& b) const {
			long int l;
			if((l=left(a,b,reference))) {
				return l>0;
			}
			if((l=distancesquare(a,reference)-distancesquare(b,reference))) {
				return l>0;
			}
			return 0;
		}
	private:
		point reference;
};
void convex_hull(int argc,char* argv[],long unsigned int* h,point* output,const long unsigned int n,const point* input) {
	if(n==1) {
		*h=1;
		output[0].x=input[0].x;
		output[0].y=input[0].y;
		return;
	}
	if(n==2) {
		*h=2;
		output[0].x=input[0].x;
		output[0].y=input[0].y;
		output[1].x=input[1].x;
		output[1].y=input[1].y;
		return;
	}
	const point* p=max_element(input,input+n,rightmost_lowest());
	comparator comparatorA(*p);
	set<point,comparator> s(input,input+n,comparatorA);
	deque<point> W;
	W.push_back(*p);
	W.push_back(*s.begin());
	set<point,comparator>::iterator i=++s.begin();
	while(i!=s.end()) {
		point pt1=*W.rbegin();
		point pt2=*(W.rbegin()+1);
		if(left(pt2,pt1,*i)>0) {
			W.push_back(*i);
			++i;
		}
		else {
			W.pop_back();
		}
	}
	*h=W.size()-1;
	long unsigned int z=0;
	for(deque<point>::iterator i=W.begin();i!=W.end()-1;++i) {
		point& p=output[z++];
		p.x=i->x;
		p.y=i->y;
		//cout<<p.x<<", "<<p.y<<endl;
	}
}

