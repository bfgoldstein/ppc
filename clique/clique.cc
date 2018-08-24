#include <stdio.h>
#include <sys/timeb.h>
#include <time.h>
#include "clique.hh"

set<set<unsigned int> > output;

//imprime um clique
void print_set(set<unsigned int> s) {
	for(set<unsigned int>::iterator it=s.begin();it!=s.end();it++) printf("%d ", *it);
}

//retorna 1 se o conjunto de nos nao formam um clique, ou seja, se o conjunto eh independente
int is_ind(const set<unsigned int> s, const set<set<unsigned int> > clique2) {
	for(set<unsigned int>::iterator it1=s.begin();it1!=s.end();it1++) {
		for(set<unsigned int>::iterator it2=it1;it2!=s.end();it2++) {
			if(*it1!=*it2) {
				set<unsigned int> t;
				t.insert(*it1);
				t.insert(*it2);
				if(clique2.find(t)!=clique2.end()) return(0);
				t.clear();
			}
		}
	}
	return(1);
}

//converte os cliques de tamanho 2 para os conjuntos independentes correspondentes
void clique2_to_ind2(unsigned int n, const set<set<unsigned int> > clique2, map<set<unsigned int>, set<unsigned int> >& ind2) {
	for(unsigned int i=0;i<n;i++) {
		for(unsigned int j=i+1;j<n;j++) {
			set<unsigned int> s, k;
			s.insert(i);
			k.insert(i);
			k.insert(j);
			if(clique2.find(k)==clique2.end()) ind2[s].insert(j);
			s.clear();
			k.clear();
		}
	}
}

//realiza uma busca em largura por cliques maximais, e adiciona em output os cliques maximais encontrados
void bfs_branch_bound(const set<set<unsigned int> > clique2, map<set<unsigned int>, set<unsigned int> >& ind) {
	do {
		map<set<unsigned int>, set<unsigned int> > next;
		for(map<set<unsigned int>, set<unsigned int> >::iterator it1=ind.begin();it1!=ind.end();it1++) {
			for(set<unsigned int>::iterator it2=(it1->second).begin();it2!=(it1->second).end();it2++) {
				for(set<unsigned int>::iterator it3=it2;it3!=(it1->second).end();it3++) {
					if(*it3!=*it2) {
						set<unsigned int> s, k;
						for(set<unsigned int>::iterator it4=(it1->first).begin();it4!=(it1->first).end();it4++) {
							s.insert(*it4);
							k.insert(*it4);
						}
						s.insert(*it2);
						k.insert(*it2);
						k.insert(*it3);
						int sub_ind=1;
						sub_ind=is_ind(k, clique2);
						if(sub_ind) next[s].insert(*it3);
						s.clear();
					}
				}
			}
		}
		if(next.size()==0) {
			for(map<set<unsigned int>, set<unsigned int> >::iterator it1=ind.begin();it1!=ind.end();it1++) {
				for(set<unsigned int>::iterator it2=(it1->second).begin();it2!=(it1->second).end();it2++) {
					//print_set(it1->first);
					set<unsigned int> s;
					for(set<unsigned int>::iterator it3=(it1->first).begin();it3!=(it1->first).end();it3++) s.insert(*it3);
					s.insert(*it2);
					output.insert(s);
				}
			}
		}
		ind.clear();
		for(map<set<unsigned int>, set<unsigned int> >::iterator it1=next.begin();it1!=next.end();it1++) {
			for(set<unsigned int>::iterator it2=(it1->second).begin();it2!=(it1->second).end();it2++) {
				set<unsigned int> s;
				for(set<unsigned int>::iterator it3=(it1->first).begin();it3!=(it1->first).end();it3++) s.insert(*it3);
				ind[s].insert(*it2);
				s.clear();
			}
		}
		next.clear();
	} while(ind.size()>0);
}

void clique(int argc, char** argv, set<set<unsigned int> >& output, const set<set<unsigned int> >& clique2, const unsigned int n) {
	map<set<unsigned int>, set<unsigned int> > ind;
	clique2_to_ind2(n, clique2, ind);
	bfs_branch_bound(clique2, ind);
}
