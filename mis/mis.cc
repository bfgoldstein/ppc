// std
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <random>

// local
#include "types.hh"
#include "algorithms.hh"

void out(const Set<Vertex>& v)
{
	for (const Vertex& i : v) std::cout << i << " ";
	std::cout << std::endl;
}

Graph in() {
	return read_graph();
}

// luby's method
Set<Vertex> mis (const Graph& g) {
	Set<Vertex> m;       // current mis (empty)
	Set<Vertex> u;// currently selected nodes (empty)
	Set<Vertex> v = g.v;// initial set of vertexes
	std::minstd_rand r;// an STL linear congruential random number gen.
	while (! v.empty ()) {
		do {
			rand_select (u, v, g, r);
		}while (u.empty ());
		set_difference (v, u);
		exclude_neighbors (u, g);
		set_difference (v, neighbors (u, g));
		set_union (m, u);
	}
	return m;
}

int main(int argc, char *argv[]) {
	out(mis(in()));
	return 0;
}

